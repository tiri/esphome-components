#include <esphome/components/sensor/sensor.h>
#include <esphome/components/uart/uart.h>
#include <esphome/core/component.h>

#include "circular_buffer.hpp"

namespace esphome {
namespace tecson {

class PCLinkPollingComponent : public PollingComponent, public uart::UARTDevice {
 public:
  PCLinkPollingComponent() : PollingComponent(15000) {}

  void set_volume_sensor(sensor::Sensor *volume_sensor) { volume_sensor_ = volume_sensor; }

  float get_setup_priority() const override { return esphome::setup_priority::HARDWARE; }

  void update() override;

 private:
  sensor::Sensor *volume_sensor_;
  circular_buffer<uint8_t, 20> buffer_{};
};

}  // namespace tecson
}  // namespace esphome
