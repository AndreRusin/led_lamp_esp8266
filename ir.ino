#ifdef ESP_USE_IR

void irTick()
{
  if (irrecv.decode(&results)) {
    String irCode = resultToHexidecimal(&results);

    // вкл
    if (irCode == "0xF7C03F") {
      if (dawnFlag == true) // если выключен
      {
        manualOff = true;
        dawnFlag = false;
        FastLED.setBrightness(modes[currentMode].Brightness);
        changePower();
      }
      settChanged = true;
      eepromTimeout = millis();
      loadingFlag = true;

      #if (USE_MQTT)
        if (espMode == 1U)
        {
          MqttManager::needToPublish = true;
        }
      #endif
    }
    // выкл
    if (irCode == "0xF740BF") {
      if (dawnFlag == false) // если включен
      {
        ONflag = !ONflag;
        changePower();
      }
      settChanged = true;
      eepromTimeout = millis();
      loadingFlag = true;

      #if (USE_MQTT)
        if (espMode == 1U)
        {
          MqttManager::needToPublish = true;
        }
      #endif
    }

    // след эффект
    if (ONflag && irCode == "0xF7708F") {
      if (++currentMode >= (int8_t)MODE_AMOUNT) currentMode = 0;
      FastLED.setBrightness(modes[currentMode].Brightness);
      loadingFlag = true;
      settChanged = true;
      eepromTimeout = millis();
      FastLED.clear();
      delay(1);

      #if (USE_MQTT)
      if (espMode == 1U)
      {
        MqttManager::needToPublish = true;
      }
      #endif
    }

    // пред эффект
    if (ONflag && irCode == "0xF730CF") {
      if (--currentMode < 0) currentMode = MODE_AMOUNT - 1;
      FastLED.setBrightness(modes[currentMode].Brightness);
      loadingFlag = true;
      settChanged = true;
      eepromTimeout = millis();
      FastLED.clear();
      delay(1);

      #if (USE_MQTT)
      if (espMode == 1U)
      {
        MqttManager::needToPublish = true;
      }
      #endif
    }

    // 6H - смена рабочего режима лампы: с WiFi точки доступа на WiFi клиент или наоборот
    if (ONflag && irCode == "0xF7E817") {
      espMode = (espMode == 0U) ? 1U : 0U;
      EepromManager::SaveEspMode(&espMode);

      #ifdef GENERAL_DEBUG
      LOG.printf_P(PSTR("Рабочий режим лампы изменён и сохранён в энергонезависимую память\nНовый рабочий режим: ESP_MODE = %d, %s\nРестарт...\n"),
        espMode, espMode == 0U ? F("WiFi точка доступа") : F("WiFi клиент (подключение к роутеру)"));
      delay(1000);
      #endif

      showWarning(CRGB::Red, 3000U, 500U);                    // мигание красным цветом 3 секунды - смена рабочего режима лампы, перезагрузка
      ESP.restart();
    }

    // яркость +
    if (ONflag && irCode == "0xF700FF") {
      uint8_t delta = modes[currentMode].Brightness < 10U // определение шага изменения яркости: при яркости [1..10] шаг = 1, при [11..16] шаг = 3, при [17..255] шаг = 15
          ? 1U
          : 15U;
        modes[currentMode].Brightness =
          constrain(modes[currentMode].Brightness + delta, 1, 255);
        FastLED.setBrightness(modes[currentMode].Brightness);

        #ifdef GENERAL_DEBUG
        LOG.printf_P(PSTR("Новое значение яркости: %d\n"), modes[currentMode].Brightness);
        #endif
    }

    // яркость -
    if (ONflag && irCode == "0xF7807F") {
      uint8_t delta = modes[currentMode].Brightness < 10U // определение шага изменения яркости: при яркости [1..10] шаг = 1, при [11..16] шаг = 3, при [17..255] шаг = 15
          ? 1U
          : 15U;
        modes[currentMode].Brightness =
          constrain(modes[currentMode].Brightness - delta, 1, 255);
        FastLED.setBrightness(modes[currentMode].Brightness);

        #ifdef GENERAL_DEBUG
        LOG.printf_P(PSTR("Новое значение яркости: %d\n"), modes[currentMode].Brightness);
        #endif
    }

    // изменение скорости + зел(10)
    if (ONflag && irCode == "0xF7906F") {
      modes[currentMode].Speed = constrain( modes[currentMode].Speed + 1, 1, 255);

      #ifdef GENERAL_DEBUG
        LOG.printf_P(PSTR("Новое значение скорости: %d\n"), modes[currentMode].Speed);
      #endif
    }

    // изменение скорости - голуб(18)
    if (ONflag && irCode == "0xF78877") {
      modes[currentMode].Speed = constrain(modes[currentMode].Speed - 1, 1, 255);

      #ifdef GENERAL_DEBUG
        LOG.printf_P(PSTR("Новое значение скорости: %d\n"), modes[currentMode].Speed);
      #endif
    }

    // изменение масштаба + красн(9)
    if (ONflag && irCode == "0xF710EF") {
      modes[currentMode].Scale = constrain( modes[currentMode].Scale + 1, 1, 100);

      #ifdef GENERAL_DEBUG
        LOG.printf_P(PSTR("Новое значение масштаба: %d\n"), modes[currentMode].Scale);
      #endif
    }
    // изменение масштаба - синяя(11)
    if (ONflag && irCode == "0xF750AF") {
      modes[currentMode].Scale = constrain( modes[currentMode].Scale - 1, 1, 100);

      #ifdef GENERAL_DEBUG
        LOG.printf_P(PSTR("Новое значение масштаба: %d\n"), modes[currentMode].Scale);
      #endif
    }

    irrecv.resume();
  }

  // // четырёхкратное нажатие
  // if (clickCount == 4U)
  // {
  //   #ifdef OTA
  //   if (otaManager.RequestOtaUpdate())
  //   {
  //     ONflag = true;
  //     currentMode = EFF_MATRIX;                             // принудительное включение режима "Матрица" для индикации перехода в режим обновления по воздуху
  //     FastLED.clear();
  //     delay(1);
  //     changePower();
  //   }
  //   #endif
  // }
}
#endif
