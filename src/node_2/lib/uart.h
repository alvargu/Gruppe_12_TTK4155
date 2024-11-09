
// UART is connected to the ATmega16U2 on the Arduino, which acts as a USB serial device.
// This module hooks into the stdio functions, by spoofing several system calls
//
// Unfortunately, for some unknown reason `scanf` does not work as expected. Use 
// `uart_flush` and `sscanf` instead (see example below)
//
// Internally, receiving is handled with interrupts and a ring buffer, so no characters
// are lost, until the buffer is full. If necessary, you can change this buffer size in 
// uart.c


// Initialize. Hooks stdio functions (like `printf`)
void uart_init(uint32_t cpufreq, uint32_t baudrate);

// Send a single character
// Prefer using `printf` instead
void uart_tx(uint8_t val);

// Read a single character
// Prefer using `uart_flush` and `sscanf` instead (see below)
uint8_t uart_rx(uint8_t* val);

// Flush the internal ring buffer into your own buffer
// Example (`scanf` workaround):
//    int result;
//    char buf[80] = {0};
//
//    uart_flush(buf, sizeof(buf)/sizeof(buf[0]));
//    int numFilled = sscanf(buf, "%d", &result);
//    if(numFilled == 1){
//        printf("%d\n", result);
//    }
int uart_flush(char* buf, int len);

   