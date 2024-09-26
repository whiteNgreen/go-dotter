#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include <character/camerapivot.h>
#include <character/playernode.h>
#include <components/grapplecomponent.h>
#include <components/inputcomponent.h>
#include <components/parrycomponent.h>
#include <mainnode.h>
#include <core/nodecomponent.hpp>

using namespace godot;

void init_gameplay_plugin_module(godot::ModuleInitializationLevel p_level) {
	if (p_level != godot::ModuleInitializationLevel::MODULE_INITIALIZATION_LEVEL_SCENE) { return; }
	godot::ClassDB::register_class<MainNode>();
	godot::ClassDB::register_class<CameraPivot>();
	godot::ClassDB::register_class<PlayerNode>();

	// Components
	godot::ClassDB::register_class<InputComponent>();
	godot::ClassDB::register_abstract_class<NodeComponent>();
	godot::ClassDB::register_class<GrappleComponent>();
	godot::ClassDB::register_class<ParryComponent>();
}

void uninit_gameplay_plugin_module(godot::ModuleInitializationLevel p_level) {
	if (p_level != godot::ModuleInitializationLevel::MODULE_INITIALIZATION_LEVEL_SCENE) { return; }
}

/// Entry point for plugin
// Name has to match ${PROJECT_NAME} from CMake configuration
// In the CMake the '-' dashes will be replaced with underscore to match this function name
extern "C" {
GDExtensionBool GDE_EXPORT gameplay_plugin_init(GDExtensionInterfaceGetProcAddress p_get_proc_address,
		const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization* r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(init_gameplay_plugin_module);
	init_obj.register_terminator(uninit_gameplay_plugin_module);
	init_obj.set_minimum_library_initialization_level(
			godot::ModuleInitializationLevel::MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}