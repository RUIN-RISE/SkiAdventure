#include "app/App.h"

int main(){
	std::unique_ptr<AirApp> app(std::make_unique<AirApp>());

	if (!app->initialize()) {
		fl_alert("Initialization failed!");
		return 1;
	}

	app->show_main_window();

	return Fl::run();
}
