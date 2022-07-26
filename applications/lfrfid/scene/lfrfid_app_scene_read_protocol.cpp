#include "lfrfid_app_scene_read_protocol.h"
#include "../helpers/key_info.h"


void LfRfidAppSceneReadProtocol::on_enter(LfRfidApp* app, bool need_restore) {
    auto submenu = app->view_controller.get<SubmenuVM>();

    for (auto p : AllKeyTypes) {
        submenu->add_item(lfrfid_key_get_type_string(p), (uint32_t)p, submenu_callback, app);
    }

    if(need_restore) {
        submenu->set_selected_item(submenu_item_selected);
    }

    app->view_controller.switch_to<SubmenuVM>();
}

bool LfRfidAppSceneReadProtocol::on_event(LfRfidApp* app, LfRfidApp::Event* event) {
    bool consumed = false;
    if (event->type == LfRfidApp::EventType::MenuSelected) {
        app->selected_key_type = event->payload.selected_key_type;
        app->protocol_selected = true;
        consumed = true;
        app->scene_controller.switch_to_next_scene(LfRfidApp::SceneType::Read);
    }
    return consumed;
}

void LfRfidAppSceneReadProtocol::on_exit(LfRfidApp* app) {
    app->view_controller.get<SubmenuVM>()->clean();
}

void LfRfidAppSceneReadProtocol::submenu_callback(void* context, uint32_t index) {
    LfRfidApp* app = static_cast<LfRfidApp*>(context);
    LfRfidApp::Event event;

    event.type = LfRfidApp::EventType::MenuSelected;
    event.payload.menu_index = index;
    event.payload.selected_key_type = AllKeyTypes[index];

    app->view_controller.send_event(&event);
}
