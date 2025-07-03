#include "app/App.h"

int main(){
	std::unique_ptr<App> app(std::make_unique<App>());

	if (!app->initialize()) {
		fl_alert("Initialization failed!");
		return 1;
	}

	app->show_main_window();

	return Fl::run();
}
