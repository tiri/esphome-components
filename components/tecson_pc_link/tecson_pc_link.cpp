#include "tecson_pc_link.hpp"

static const char *TAG = "tecson-pc-link";

namespace esphome {
namespace tecson {

void PCLinkPollingComponent::update() {
    int bytes_to_read = this->available();
    if (bytes_to_read < 1) return;

    for (int i = bytes_to_read; i > 0; i--) {
        buff.push(this->read());
    }

    ESP_LOGD(TAG, "bytes read: %d.", bytes_to_read);

    const auto current = buff.read_all();
    if (current[0] != 0xFF || current[1] != 0x02 || current[19] != 0x03) return;

    // todo: validate checksum

    if (volume_sensor_ != nullptr) {
        int tank_volume = (current[8] >> 4) * 1000 + (current[8] & 0xF) * 100 +
                         (current[9] >> 4) * 10 + (current[9] & 0xF);
        ESP_LOGD(TAG, "Tank volume: %d", tank_volume);
        volume_sensor_->publish_state(tank_volume);
    }

    buff.flush();
}

}  // namespace tecson
}  // namespace esphome