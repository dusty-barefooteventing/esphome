#include "emporia_vue.h"
#include "esphome/core/hal.h"
#include "esphome/core/log.h"

namespace esphome {
namespace emporia_vue {

static const char *const TAG = "emporia_vue";

void EmporiaVueComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Emporia Vue");
  LOG_I2C_DEVICE(this);

  for (auto *phase : this->phases_) {
    std::string wire;
    switch (phase->get_input_wire()) {
      case PhaseInputWire::BLACK:
        wire = "BLACK";
        break;
      case PhaseInputWire::RED:
        wire = "RED";
        break;
      case PhaseInputWire::BLUE:
        wire = "BLUE";
        break;
    }
    ESP_LOGCONFIG(TAG, "  Phase");
    ESP_LOGCONFIG(TAG, "    Wire: %s", wire.c_str());
    ESP_LOGCONFIG(TAG, "    Calibration: %f", phase->get_calibration());
    LOG_SENSOR("    ", "Voltage", phase->get_voltage_sensor());
  }

  for (auto *ct_clamp : this->ct_clamps_) {
    ESP_LOGCONFIG(TAG, "  CT Clamp");
    ESP_LOGCONFIG(TAG, "    Phase Calibration: %f", ct_clamp->get_phase()->get_calibration());
    ESP_LOGCONFIG(TAG, "    CT Port Index: %d", ct_clamp->get_input_port());
    LOG_SENSOR("    ", "Power", ct_clamp->get_power_sensor());
    LOG_SENSOR("    ", "Current", ct_clamp->get_current_sensor());
  }
}

void EmporiaVueComponent::update() {
  SensorReading sensor_reading;

  i2c::ErrorCode err = read(reinterpret_cast<uint8_t *>(&sensor_reading), sizeof(sensor_reading));

  if (err != i2c::ErrorCode::ERROR_OK) {
    ESP_LOGE(TAG, "Failed to read from sensor due to I2C error %d", err);
    return;
  }

  if (!sensor_reading.is_unread) {
    ESP_LOGV(TAG, "Ignoring sensor reading that is marked as read");
    return;
  }


  if (sensor_reading.end != 0) {
    ESP_LOGE(TAG, "sensor_reading.is_unread: %x", sensor_reading.is_unread);
    ESP_LOGE(TAG, "sensor_reading.checksum: %x", sensor_reading.checksum);
    ESP_LOGE(TAG, "sensor_reading.unknown: %x", sensor_reading.unknown);
    ESP_LOGE(TAG, "sensor_reading.sequence_num: %x", sensor_reading.sequence_num);/*
    ESP_LOGE(TAG, "sensor_reading.power[0]: %x", sensor_reading.power[0]);
    ESP_LOGE(TAG, "sensor_reading.power[1]: %x", sensor_reading.power[1]);
    ESP_LOGE(TAG, "sensor_reading.power[2]: %x", sensor_reading.power[2]);
    ESP_LOGE(TAG, "sensor_reading.power[3]: %x", sensor_reading.power[3]);
    ESP_LOGE(TAG, "sensor_reading.power[4]: %x", sensor_reading.power[4]);
    ESP_LOGE(TAG, "sensor_reading.power[5]: %x", sensor_reading.power[5]);
    ESP_LOGE(TAG, "sensor_reading.power[6]: %x", sensor_reading.power[6]);
    ESP_LOGE(TAG, "sensor_reading.power[7]: %x", sensor_reading.power[7]);
    ESP_LOGE(TAG, "sensor_reading.power[8]: %x", sensor_reading.power[8]);
    ESP_LOGE(TAG, "sensor_reading.power[9]: %x", sensor_reading.power[9]);
    ESP_LOGE(TAG, "sensor_reading.power[10]: %x", sensor_reading.power[10]);
    ESP_LOGE(TAG, "sensor_reading.power[11]: %x", sensor_reading.power[11]);
    ESP_LOGE(TAG, "sensor_reading.power[12]: %x", sensor_reading.power[12]);
    ESP_LOGE(TAG, "sensor_reading.power[13]: %x", sensor_reading.power[13]);
    ESP_LOGE(TAG, "sensor_reading.power[14]: %x", sensor_reading.power[14]);
    ESP_LOGE(TAG, "sensor_reading.power[15]: %x", sensor_reading.power[15]);
    ESP_LOGE(TAG, "sensor_reading.power[16]: %x", sensor_reading.power[16]);
    ESP_LOGE(TAG, "sensor_reading.power[17]: %x", sensor_reading.power[17]);
    ESP_LOGE(TAG, "sensor_reading.power[18]: %x", sensor_reading.power[18]);*/
    ESP_LOGE(TAG, "sensor_reading.voltage[0]: %x", sensor_reading.voltage[0]);
    ESP_LOGE(TAG, "sensor_reading.voltage[1]: %x", sensor_reading.voltage[1]);
    ESP_LOGE(TAG, "sensor_reading.voltage[2]: %x", sensor_reading.voltage[2]);
    ESP_LOGE(TAG, "sensor_reading.frequency: %x", sensor_reading.frequency);
    ESP_LOGE(TAG, "sensor_reading.degrees[0]: %x", sensor_reading.degrees[0]);
    ESP_LOGE(TAG, "sensor_reading.degrees[1]: %x", sensor_reading.degrees[1]);
    ESP_LOGE(TAG, "sensor_reading.current[0]: %x", sensor_reading.current[0]);
    ESP_LOGE(TAG, "sensor_reading.current[1]: %x", sensor_reading.current[1]);
    ESP_LOGE(TAG, "sensor_reading.current[2]: %x", sensor_reading.current[2]);
    ESP_LOGE(TAG, "sensor_reading.current[3]: %x", sensor_reading.current[3]);
    ESP_LOGE(TAG, "sensor_reading.current[4]: %x", sensor_reading.current[4]);
    ESP_LOGE(TAG, "sensor_reading.current[5]: %x", sensor_reading.current[5]);
    ESP_LOGE(TAG, "sensor_reading.current[6]: %x", sensor_reading.current[6]);
    ESP_LOGE(TAG, "sensor_reading.current[7]: %x", sensor_reading.current[7]);
    ESP_LOGE(TAG, "sensor_reading.current[8]: %x", sensor_reading.current[8]);
    ESP_LOGE(TAG, "sensor_reading.current[9]: %x", sensor_reading.current[9]);
    ESP_LOGE(TAG, "sensor_reading.current[10]: %x", sensor_reading.current[10]);
    ESP_LOGE(TAG, "sensor_reading.current[11]: %x", sensor_reading.current[11]);
    ESP_LOGE(TAG, "sensor_reading.current[12]: %x", sensor_reading.current[12]);
    ESP_LOGE(TAG, "sensor_reading.current[13]: %x", sensor_reading.current[13]);
    ESP_LOGE(TAG, "sensor_reading.current[14]: %x", sensor_reading.current[14]);
    ESP_LOGE(TAG, "sensor_reading.current[15]: %x", sensor_reading.current[15]);
    ESP_LOGE(TAG, "sensor_reading.current[16]: %x", sensor_reading.current[16]);
    ESP_LOGE(TAG, "sensor_reading.current[17]: %x", sensor_reading.current[17]);
    ESP_LOGE(TAG, "sensor_reading.current[18]: %x", sensor_reading.current[18]);
    ESP_LOGE(TAG, "Failed to read from sensor due to a malformed reading, should end in null bytes but is %x",
             sensor_reading.end);
    return;
  }

  ESP_LOGV(TAG, "Received sensor reading with sequence #%d", sensor_reading.sequence_num);

  if (this->last_sequence_num_ && sensor_reading.sequence_num > this->last_sequence_num_ + 1) {
    ESP_LOGW(TAG, "Detected %d missing reading(s), data may not be accurate!",
             sensor_reading.sequence_num - this->last_sequence_num_ - 1);
  }

  for (auto *phase : this->phases_) {
    phase->update_from_reading(sensor_reading);
  }
  for (auto *ct_clamp : this->ct_clamps_) {
    ct_clamp->update_from_reading(sensor_reading);
  }

  this->last_sequence_num_ = sensor_reading.sequence_num;

  this->callback_.call();
}

void EmporiaVueComponent::add_on_update_callback(std::function<void()> &&callback) {
  this->callback_.add(std::move(callback));
}

void PhaseConfig::update_from_reading(const SensorReading &sensor_reading) {
  if (this->voltage_sensor_) {
    float calibrated_voltage = sensor_reading.voltage[this->input_wire_] * this->calibration_;
    this->voltage_sensor_->publish_state(calibrated_voltage);
  }

  uint16_t raw_frequency = sensor_reading.frequency;
  // validation that these sensors are allowed on this phase is done in the codegen stage
  if (this->frequency_sensor_) {
    // see https://github.com/emporia-vue-local/esphome/pull/88 for constant explanation
    float frequency = 25310.0f / (float) raw_frequency;
    this->frequency_sensor_->publish_state(frequency);
  }
  if (this->phase_angle_sensor_) {
    uint16_t raw_phase_angle = sensor_reading.degrees[((uint8_t) this->input_wire_) - 1];
    float phase_angle = ((float) raw_phase_angle) * 360.0f / ((float) raw_frequency);
    // this is truncated to a uint16_t on the vue 2
    this->phase_angle_sensor_->publish_state(phase_angle);
  }
}

int32_t PhaseConfig::extract_power_for_phase(const ReadingPowerEntry &power_entry) {
  switch (this->input_wire_) {
    case PhaseInputWire::BLACK:
      return power_entry.phase_black;
    case PhaseInputWire::RED:
      return power_entry.phase_red;
    case PhaseInputWire::BLUE:
      return power_entry.phase_blue;
    default:
      ESP_LOGE(TAG, "Unsupported phase input wire, this should never happen");
      return -1;
  }
}

void CTClampConfig::update_from_reading(const SensorReading &sensor_reading) {
  if (this->power_sensor_) {
    ReadingPowerEntry power_entry = sensor_reading.power[this->input_port_];
    int32_t raw_power = this->phase_->extract_power_for_phase(power_entry);
    float calibrated_power = this->get_calibrated_power(raw_power);
    this->power_sensor_->publish_state(calibrated_power);
  }
  if (this->current_sensor_) {
    uint16_t raw_current = sensor_reading.current[this->input_port_];
    double raw_current_d = (double) raw_current;
    double scalar;
    if (this->input_port_ <= CTInputPort::C) {
      scalar = 775.0 / 42624.0;
    } else {
      scalar = 775.0 / 170496.0;
    }
    this->current_sensor_->publish_state(raw_current_d * scalar);
  }
}

float CTClampConfig::get_calibrated_power(int32_t raw_power) const {
  float calibration = this->phase_->get_calibration();

  float correction_factor = (this->input_port_ < 3) ? 5.5 : 22;

  return (raw_power * calibration) / correction_factor;
}

}  // namespace emporia_vue
}  // namespace esphome
