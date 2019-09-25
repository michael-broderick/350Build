

static void sensor_read(void)
{
    fsr1Read();
        fsr2Read();
            utsRead();
            return;
}

void fsr1Read(void)
{
    uint32_t fsr1_reading = 0;
    //Multisampling
    for (int i = 0; i < NO_OF_SAMPLES; i++)
    {
        if (unit == ADC_UNIT_1)
        {
            fsr1_reading += adc1_get_raw((adc1_channel_t)fsr1Channel);
        }
        else
        {
            int raw;
            adc2_get_raw((adc2_channel_t)fsr1Channel, ADC_WIDTH_BIT_12, &raw);
            fsr1_reading += raw;
        }
    }
    fsr1_reading /= NO_OF_SAMPLES;
    //Convert adc_reading to voltage in mV
    uint32_t voltage = esp_adc_cal_raw_to_voltage(fsr1_reading, adc_chars);
    printf("FSR1 Reading --> Raw: %d\tVoltage: %dmV\n", fsr1_reading, voltage);
    vTaskDelay(pdMS_TO_TICKS(1000));
    fsr1Value = (int)fsr1_reading;
}
void fsr2Read(void)
{
    uint32_t fsr2_reading = 0;
    //Multisampling
    for (int i = 0; i < NO_OF_SAMPLES; i++)
    {
        if (unit == ADC_UNIT_1)
        {
            fsr2_reading += adc1_get_raw((adc1_channel_t)fsr2Channel);
        }
        else
        {
            int raw;
            adc2_get_raw((adc2_channel_t)fsr2Channel, ADC_WIDTH_BIT_12, &raw);
            fsr2_reading += raw;
        }
    }
    fsr2_reading /= NO_OF_SAMPLES;
    //Convert adc_reading to voltage in mV
    uint32_t voltage = esp_adc_cal_raw_to_voltage(fsr2_reading, adc_chars);
    printf("FSR2 Reading --> Raw: %d\tVoltage: %dmV\n", fsr2_reading, voltage);
    vTaskDelay(pdMS_TO_TICKS(1000));
    fsr2Value = (int)fsr2_reading;
}

void utsRead(void)
{
    uint32_t uts_reading = 0;
    //Multisampling
    for (int i = 0; i < NO_OF_SAMPLES; i++)
    {
        if (unit == ADC_UNIT_1)
        {
            uts_reading += adc1_get_raw((adc1_channel_t)utsChannel);
        }
        else
        {
            int raw;
            adc2_get_raw((adc2_channel_t)utsChannel, ADC_WIDTH_BIT_12, &raw);
            uts_reading += raw;
        }
    }
    uts_reading /= NO_OF_SAMPLES;
    //Convert adc_reading to voltage in mV
    uint32_t voltage = esp_adc_cal_raw_to_voltage(uts_reading, adc_chars);
    printf("FSR1 Reading --> Raw: %d\tVoltage: %dmV\n", uts_reading, voltage);
    vTaskDelay(pdMS_TO_TICKS(1000));
    usds_distance = (float)voltage / 2.52;
}
