/*
 * info.h
 *
 *  Created on: 7 Feb 2019
 *      Author: alex
 */

#ifndef INFO_H_
#define INFO_H_

/*
 * =============================================================
 * Regelung zur Warmwasseraufbereitung mithilfe von Solarenergie
 * =============================================================
 *
 * Hardware
 * ========
 *
 * LED
 * ---
 * ledGreen (Statusindikator der Wasserpumpe)
 * - an = Wasserpumpe läuft
 * - aus = Wasserpumpe läuft nicht
 *
 * ledRed (Betriebsmodus-Anzeige)
 * - an = Einstellungsmodus
 * - aus = Konstrollmodus
 * - blinkend = Fehler ??
 *
 * Button
 * ------
 * buttonLeft
 * - im Kontrollmodus = Wechsel zu Einstellungsmodus
 * - im Einstellungsmodus = Zieltemperatur - 1 °C
 * buttonRight
 * - im Kontrollmodus = Wechsel der Temperatursensorwerte auf Displayanzeige (water, hot, cold)
 * - in Einstellungsmodus = Zieltemperatur + 1 °C
 *
 * Display
 * -------
 * displayHeart
 * - zeigt, dass die Anwendung läuft
 * displayNumber
 * - zeigt eine Zahl im Kontext der Anwendung an
 * ...
 *
 * Temperatursensor
 * ----------------
 * sensorWater (Temperatur des Nutzwassers)
 * - liefert tempWater
 * sensorHot (Temperatur der Flüssigkeit vor Wärmeabgabe)
 * - liefert tempHot
 * sensorCold (Temperatur der Flüssigkeit nach Wärmeabgabe)
 * - liefert tempCold
 *
 * Software
 * ========
 *
 * Systemkonstante
 * ---------------
 * timeoutControl [s] (Zeitdauer zwischen den Kontrollvorgängen (nur für Kontrollbetrieb relevant))
 * timeoutSetting [s] (Inaktivitätsdauer bis zum Wechsel von Einstellungsbetrieb auf Kontrollbetrieb)
 * tempTolerance [°C] (absolute Toleranzabweichung zur Zieltemperatur)
 * tempTargetInitial [°C] (Startwert für Zieltemperatur in 1 °C Schritten)
 * tempMax [°C] (Maximaltemperatur welche bei Überschreitung den Regelkreis ausschaltet. tempHot > tempMax)
 * tempMin [°C] (Minimaltemperatur welche bei Unterschreitung den Regelkreis ausschaltet. tempHot < tempMin || tempCold < tempMin)
 *
 * Einstellungen
 * -------------
 * tempTarget (Zieltemperatur einstellbar in 1 °C Schritten)
 *
 * Logik
 * -----
 *
 * Einstellungsbetrieb:
 * Wird bei Betätigung von buttonLeft im Kontrollbetrieb aktiv.
 * Währenddessen leuchtet ledRed.
 * buttonLeft senkt die Zieltemperatur und setzt timeoutCounter zurück.
 * buttonRight erhöht die Zieltemperatur und setzt timeoutCounter zurück.
 * displayNumber zeigt nun durchgehend den Wert der Zieltemperatur.
 * Nach timeoutSetting (ohne Aktivität) erfolgt Wechsel zu Kontrollbetrieb.
 *
 * Kontrollbetrieb:
 * Ist standardmäßig aktiv.
 * Währenddessen ist ledRed aus.
 * ledGreen ist abhängig von der Erreichung der Zieltemperatur an oder aus.
 * buttonLeft ermöglicht den Wechsel zum Einstellungsbetrieb.
 * buttonRight wechselt die Darstellung der Ist-Temperaturen in der Reihenfolge water, hot, cold.
 * displayNumber zeigt nun die aktuelle Ist-Temperatur des interessierten Wertes.
 *
 * Ablauf
 * ======
 *
 * Kontrollbetrieb
 * ---------------
 * 1. Temperaturen lesen
 * 2. im Aufheiz-Status:
 *    - wenn tempWater < tempTarget + temp und tempHot > tempCold
 *
 * 2. Zustand von ledGreen prüfen (
 *
 *
 * Einstellungsablauf:
 * -------------------------------------------------------------
 *
 */

/**
 * main.c
 */

/*
 * global state
 * ============
 */

/*
 #define TEMP_TARGET_INITIAL 40
 #define TEMP_MIN 5
 #define TEMP_MAX 95


 // forward declarations
 void onButtonLeftPress();
 void onButtonRightPress();

 static int tempTarget = TEMP_TARGET_INITIAL;

 void goToSettingMode() {
 // ...
 mode = SETTING;
 }

 void onButtonLeftPress() {
 if (mode == CONTROL) {
 goToSettingMode();
 } else {
 // prevent going too low
 if (tempTarget > TEMP_MIN) {
 tempTarget--;
 }
 // update display?
 // revert inactivity duration counter
 }
 }

 void onButtonRightPress() {
 if (mode == CONTROL) {
 // update display?
 } else {
 // prevent going too high
 if (tempTarget < TEMP_MAX) {
 tempTarget++;
 }
 // update display?
 // revert inactivity duration counter
 }
 }
 */

#endif /* INFO_H_ */
