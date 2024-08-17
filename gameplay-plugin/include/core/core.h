#ifndef GD_CORECORE_PLUGIN_GAMEPLAY_H
#define GD_CORECORE_PLUGIN_GAMEPLAY_H

#include <chrono>
#include <godot_cpp/classes/engine.hpp>
#include <typeinfo>

#define ASSERT(expr, msg) __m_assert(#expr, expr, __FILE__, __LINE__, msg)
void __m_assert(const char* expr_str, bool expr, const char* file, int line, const char* msg);

// Distinction between editor-mode and in-game
#define RETURN_IF_EDITOR                                                                                               \
	if (godot::Engine::get_singleton()->is_editor_hint()) {                                                            \
		return;                                                                                                        \
	}

#define GETNAME(class_name)                                                                                            \
	String get_class_name() const { return #class_name; }
#define DEFAULT_PROPERTY(class_name)                                                                                   \
	ClassDB::bind_method(D_METHOD("get_class_name"), &class_name::get_class_name);                                     \
	ClassDB::add_property(#class_name,                                                                                 \
			PropertyInfo(Variant::STRING, "class_name", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_DEFAULT), "",           \
			"get_class_name");

struct Log {
	enum class Level : uint8_t { DEBUG, INFO, WARN, ERROR };
	static void debug(const char* msg);
	static void info(const char* msg);
	static void warn(const char* msg);
	static void error(const char* msg);
};

// From the context of the MainScene
namespace NodePaths {

	constexpr const char* player = "/root/Mainscene/PlayerNode";
	constexpr const char* camera_pivot = "/root/Mainscene/PlayerNode/CameraPivot";
	constexpr const char* camera = ("%s/Camera", camera_pivot);

} //namespace NodePaths

namespace InputMap {

	constexpr const char* move_left = "move_left";
	constexpr const char* move_right = "move_right";
	constexpr const char* move_forward = "move_forward";
	constexpr const char* move_backward = "move_backward";

	constexpr const char* jump = "jump";
	constexpr const char* attack = "attack";
	constexpr const char* parry = "parry";
	constexpr const char* grapplehook = "grapplehook";

	constexpr const char* camera_left = "camera_left";
	constexpr const char* camera_right = "camera_right";
	constexpr const char* camera_up = "camera_up";
	constexpr const char* camera_down = "camera_down";

	constexpr const char* pause_menu = "pause_menu";
	constexpr const char* toggle_screen_mode = "toggle_screen_mode";

	// Some Built-in actions
	constexpr const char* ui_up = "ui_up";
	constexpr const char* ui_down = "ui_down";

} // namespace InputMap

enum class EInputMode : uint8_t {
	NONE = 0,
	MOUSE_N_KEYBOARD = 1,
	JOYPAD = 2,
};

enum class EInputAction : int {
	NONE = -1,
	// Game action
	// MOVE_LEFT,
	// MOVE_RIGHT,
	JUMP,
	PAUSE_MENU,
	TOGGLE_SCREEN_MODE,

	// Some Built-in Actions
	UI_ACCEPT,
	UI_SELECT,
	UI_CANCEL,
	UI_FOCUS_NEXT,
	UI_FOCUS_PREV,
	UI_LEFT,
	UI_RIGHT,
	UI_UP,
	UI_DOWN,
	UI_MENU,
};

enum class EInputActionType : int {
	NONE = 0,
	PRESSED,
	RELEASED,
	HELD,
	TEST,
	TES2,
};

struct InputAction {
	InputAction(EInputAction a, EInputActionType t) : action(a), type(t), timestamp(std::chrono::system_clock::now()) {}
	EInputAction action = EInputAction::NONE;
	EInputActionType type = EInputActionType::NONE;
	std::chrono::system_clock::time_point timestamp;

	bool is_action_pressed(EInputAction action) { return action == action && type == EInputActionType::PRESSED; }
	bool is_action_released(EInputAction action) { return action == action && type == EInputActionType::RELEASED; }
	bool is_action_held(EInputAction action) { return action == action && type == EInputActionType::HELD; }
	bool is_action_down(EInputAction action) {
		return action == action && (type == EInputActionType::HELD || type == EInputActionType::PRESSED);
	}
	bool received_input_within_timeframe(float timeframe_seconds) {
		float duration_since_timestamp =
				std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - timestamp)
						.count();
		float sec = (duration_since_timestamp / 1e9);
		// printf("timeframe: %f -- time: %f \n", timeframe_seconds, sec);
		return (duration_since_timestamp / 1e9) < timeframe_seconds;
	}
};

#endif // GD_CORECORE_PLUGIN_GAMEPLAY_H