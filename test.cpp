#include <GLFW/glfw3.h>
#include <gtkmm.h>
#include <math.h>
#include <time.h>

#include <boost/thread.hpp>
#include <boost/python.hpp>

#include <stdio.h>

struct State {
	boost::mutex mtx;
	bool isRunning;
	float angle;
};

// --------------- GUI -----------------

void gui_process(State& state) {
	printf("GUI Process\n");

	Gtk::Main kit;
	Gtk::Window mainWindow;

	Gtk::Button btn("test");
	mainWindow.add(btn);
	mainWindow.show_all();

	kit.run(mainWindow);

	state.isRunning = false;
}

// ------------ Renderer -----------------

void render_process(State& state) {
	printf("Render Process\n");
	float a = 0.0f;

	if (glfwInit()) {
		GLFWwindow* window = glfwCreateWindow(400, 400, "SOCS Project", NULL, NULL);

		if (window) {
			glfwMakeContextCurrent(window);

			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			glViewport(0, 0, width, height);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, 1.0, 0, 1.0, 0, 1.0);
			glMatrixMode(GL_MODELVIEW);

			while (state.isRunning) {
				{
					boost::mutex::scoped_lock(state.mtx);
					a = state.angle;
				}

				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glBegin(GL_LINES);
				glColor3f(1.0, 0.0, 0.0);
				glVertex3f(0.5, 0.5, 0.0);
				glVertex3f(0.5 + cos(a), 0.5 + sin(a), 0.0);
				glEnd();

			    glfwSwapBuffers(window);
			    glfwPollEvents();
			}

			glfwDestroyWindow(window);
		}

		glfwTerminate();
	}
}

// ---------- Simulation ------------

void simulation_process(State& state) {
	printf("Simulation Process\n");

	while (state.isRunning) {
		{
			boost::mutex::scoped_lock(state.mtx);
			state.angle += 0.01;
		}
		
		usleep(1000);
	}
}

// ---------- Main -----------------

int __main(boost::python::object callback) {
	State state;
	state.isRunning = true;
	state.angle = 0.0;

	callback();
	
	boost::thread guiProcess(boost::bind(&gui_process, boost::ref(state)));
	boost::thread renderProcess(boost::bind(&render_process, boost::ref(state)));
	boost::thread simulationProcess(boost::bind(&simulation_process, boost::ref(state)));

	guiProcess.join();
	renderProcess.join();
	simulationProcess.join();

	return 1;
}

BOOST_PYTHON_MODULE(libtest) {
    using namespace boost::python;
    def("simulate", __main);
}
