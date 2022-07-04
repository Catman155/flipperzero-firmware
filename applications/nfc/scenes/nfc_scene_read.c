#include "../nfc_i.h"
#include <dolphin/dolphin.h>

void nfc_read_worker_callback(NfcWorkerEvent event, void* context) {
    UNUSED(event);
    Nfc* nfc = context;
    view_dispatcher_send_custom_event(nfc->view_dispatcher, event);
}

void nfc_scene_read_on_enter(void* context) {
    Nfc* nfc = context;
    DOLPHIN_DEED(DolphinDeedNfcRead);

    // Setup view
    Popup* popup = nfc->popup;
    popup_set_header(popup, "Detecting\nNFC card", 70, 34, AlignLeft, AlignTop);
    popup_set_icon(popup, 0, 3, &I_RFIDDolphinReceive_97x61);

    // Start worker
    view_dispatcher_switch_to_view(nfc->view_dispatcher, NfcViewPopup);
    nfc_worker_start(
        nfc->worker, NfcWorkerStateRead, &nfc->dev->dev_data, nfc_read_worker_callback, nfc);

    nfc_blink_start(nfc);
}

bool nfc_scene_read_on_event(void* context, SceneManagerEvent event) {
    Nfc* nfc = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == NfcWorkerEventReadNfcB || event.event == NfcWorkerEventReadNfcF ||
           event.event == NfcWorkerEventReadNfcV) {
            scene_manager_next_scene(nfc->scene_manager, NfcSceneReadCardSuccess);
            consumed = true;
        } else if(event.event == NfcWorkerEventReadMifareUltralight) {
            scene_manager_next_scene(nfc->scene_manager, NfcSceneReadMifareUlSuccess);
            consumed = true;
        } else if(event.event == NfcWorkerEventReadMifareClassicDone) {
            scene_manager_next_scene(nfc->scene_manager, NfcSceneReadMifareClassicSuccess);
            consumed = true;
        } else if(event.event == NfcWorkerEventReadMifareDesfire) {
            scene_manager_next_scene(nfc->scene_manager, NfcSceneReadMifareDesfireSuccess);
            consumed = true;
        } else if(event.event == NfcWorkerEventReadBankCard) {
            scene_manager_next_scene(nfc->scene_manager, NfcSceneReadEmvDataSuccess);
            consumed = true;
        } else if(event.event == NfcWorkerEventReadMifareClassicDictAttackRequired) {
            scene_manager_next_scene(nfc->scene_manager, NfcSceneReadMifareClassic);
            consumed = true;
        }
    }
    return consumed;
}

void nfc_scene_read_on_exit(void* context) {
    Nfc* nfc = context;

    // Stop worker
    nfc_worker_stop(nfc->worker);
    // Clear view
    popup_reset(nfc->popup);

    nfc_blink_stop(nfc);
}
