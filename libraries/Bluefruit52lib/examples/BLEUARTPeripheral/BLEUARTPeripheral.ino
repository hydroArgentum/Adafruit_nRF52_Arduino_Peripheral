// BLE UART data transfer.
#include <bluefruit.h>

// Debug
#define DEBUG_FLAG 1

BLEUart bleuart; // UART over BLE peripheral.

void setup() {
  
#if(DEBUG_FLAG)
  // Wait for UART
  while(!Serial){};
  delay(500);
  Serial.begin(115200);
#endif

  // Initialize Bluetooth as Peripheral.
  Bluefruit.begin();
  Bluefruit.setTxPower(4);

  // Configure and Start BLE UART Peripheral service.
  bleuart.begin();
  bleuart.setRxCallback(prph_bleuart_rx_callback);

  // Callbacks for Peripheral
  Bluefruit.Periph.setConnectCallback(prph_connect_callback);
  Bluefruit.Periph.setDisconnectCallback(prph_disconnect_callback);

  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  
  // Include bleuart 128-bit uuid
  Bluefruit.Advertising.addService(bleuart);
  
  // Secondary Scan Response packet (optional)
  // Since there is no room for 'Name' in Advertising packet
  Bluefruit.ScanResponse.addName();
  
  /* Start Advertising
   * - Enable auto advertising if disconnected
   * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   *
   * For recommended advertising interval
   * https://developer.apple.com/library/content/qa/qa1931/_index.html
   */
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds

  // Add custom config below:
  //// (Example) Initialize digital pin 5 (D5)
  // pinMode(5, OUTPUT);
}

void loop() {
  // Nothing needed here: All code will be handled in callbacks.
}

void prph_connect_callback(uint16_t conn_handle)
{
  // Get the reference to current connection
  BLEConnection* connection = Bluefruit.Connection(conn_handle);

  char peer_name[32] = { 0 };
  connection->getPeerName(peer_name, sizeof(peer_name));

#if(DEBUG_FLAG)
  Serial.print("[Prph] Connected to ");
  Serial.println(peer_name);
#endif
}

void prph_disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;

#if(DEBUG_FLAG)
  Serial.println();
  Serial.println("[Prph] Disconnected");
#endif
}

void prph_bleuart_rx_callback(uint16_t conn_handle)
{
  (void) conn_handle;
  
  // Read data.
  char str[20+1] = { 0 };
  bleuart.read(str, 20);

#if(DEBUG_FLAG)
  Serial.print("[Prph] RX: ");
  Serial.println(str);
#endif 

  // Below is where useful code can be created/called.
}
