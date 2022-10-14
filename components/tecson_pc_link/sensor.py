import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import uart, sensor
from esphome.const import (
    CONF_ID,
    ICON_RULER,
)

DEPENDENCIES = ["uart"]

tecson_ns = cg.esphome_ns.namespace("tecson")
PCLinkPollingComponent = tecson_ns.class_("PCLinkPollingComponent", cg.PollingComponent, uart.UARTDevice)
PCLinkSensor = tecson_ns.class_("PCLinkSensor", sensor.Sensor)

CONF_VOLUME = "volume"
UNIT_LITRE = "L"

CONFIG_SCHEMA = (
    cv.Schema({
        cv.GenerateID(): cv.declare_id(PCLinkPollingComponent),
        cv.Optional(CONF_VOLUME): sensor.sensor_schema(unit_of_measurement=UNIT_LITRE, icon=ICON_RULER, accuracy_decimals=0),
    })
    .extend(uart.UART_DEVICE_SCHEMA)
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if CONF_VOLUME in config:
        sens = await sensor.new_sensor(config[CONF_VOLUME])
        cg.add(var.set_volume_sensor(sens))
