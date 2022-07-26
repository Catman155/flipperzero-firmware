#include "lfrfid_app_scene_read.h"
#include <dolphin/dolphin.h>
#include "../helpers/key_info.h"

void LfRfidAppSceneRead::on_enter(LfRfidApp* app, bool /* need_restore */) {
    auto popup = app->view_controller.get<PopupVM>();

    DOLPHIN_DEED(DolphinDeedRfidRead);
    if (app->protocol_selected) {
        app->worker.set_selected_protocol(app->selected_key_type);
        char const *str1 = "Reading\n";
        char const *str2 = lfrfid_key_get_type_string(app->selected_key_type);
        int buffer_size = strlen(str1) + strlen(str2);
        char* concatString = new char[buffer_size];
        strcpy(concatString, str1);
        strcat(concatString, str2);
        popup->set_header(concatString, 89, 34, AlignCenter, AlignTop);
    } else {
        popup->set_header("Reading\nLF RFID", 89, 34, AlignCenter, AlignTop);
    }
    popup->set_icon(0, 3, &I_RFIDDolphinReceive_97x61);


    app->view_controller.switch_to<PopupVM>();
    app->worker.start_read();
}

bool LfRfidAppSceneRead::on_event(LfRfidApp* app, LfRfidApp::Event* event) {
    bool consumed = false;

    if(event->type == LfRfidApp::EventType::Tick) {
        if(app->worker.read()) {
            DOLPHIN_DEED(DolphinDeedRfidReadSuccess);
            notification_message(app->notification, &sequence_success);
            app->scene_controller.switch_to_next_scene(LfRfidApp::SceneType::ReadSuccess);
        } else {
            if(app->worker.any_read()) {
                notification_message(app->notification, &sequence_blink_yellow_10);
            } else if(app->worker.detect()) {
                notification_message(app->notification, &sequence_blink_yellow_10);
            } else {
                notification_message(app->notification, &sequence_blink_cyan_10);
            }
        }
    }

    return consumed;
}

void LfRfidAppSceneRead::on_exit(LfRfidApp* app) {
    app->view_controller.get<PopupVM>()->clean();
    app->worker.stop_read();
}
