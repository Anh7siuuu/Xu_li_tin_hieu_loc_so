#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define MIC_PIN 2                   // Chân ADC (Microphone)             
#define OLED_RESET -1                // Reset OLED (nếu cần)
#define SAMPLES 256                // Số mẫu FFT (lũy thừa của 2)
#define SAMPLING_FREQUENCY 40000      // Tần số lấy mẫu (4kHz)
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

double vReal[SAMPLES];               // Mảng tín hiệu thực
double vImag[SAMPLES];               // Mảng tín hiệu ảo
unsigned int sampling_period_us;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);

  // Cấu hình ADC
  analogReadResolution(12);        // Độ phân giải ADC 12-bit (0-4095)
  analogSetAttenuation(ADC_11db);  // Đo dải tín hiệu (0-3.3V)


}

void fft(double *Vreal, double *vimag, int &SAMPLE, int &step){
    for(int i=0; i<SAMPLES; i++){
        vReal[i]=analogRead(MIC_PIN);
        vImag[i]=0;
        delayMicroseconds(1000/SAMPLING_FREQUENCY);
    }
    
} 

void Max_Frequency(){
    // Tìm tần số có biên độ lớn nhất
    int maxIndex = 0;
    double maxAmplitude = 0;
    for (int i = 3; i < (SAMPLES / 2); i++) {  // Duyệt qua nửa đầu phổ tần số
        if (vReal[i] > maxAmplitude) {
            maxAmplitude = vReal[i];
            maxIndex = i;
        }
    }

    double dominantFrequency = maxIndex * ((double)SAMPLING_FREQUENCY / SAMPLES);

    // Hiển thị tần số có biên độ lớn nhất lên OLED
    display.clearDisplay();  // Xóa màn hình
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Max Freq:");
    display.setCursor(0, 20);
    display.print(dominantFrequency, 2);  // Hiển thị tần số với 2 chữ số thập phân
    display.print(" Hz");

    display.display();  // Cập nhật màn hình
}      
void DisplayFullFrequencySpectrum() {
    display.clearDisplay();  // Xóa màn hình

    // Số lượng cột hiển thị
    int numBars = SCREEN_WIDTH;
    int barStep = max((SAMPLES / 2) / numBars, 1); // Bước nhảy tối thiểu là 1

    // Tìm giá trị biên độ lớn nhất để chuẩn hóa
    double maxAmplitude = 0;
    for (int i = 1; i < SAMPLES / 2; i++) {  // Bỏ qua giá trị đầu (DC offset)
        if (vReal[i] > maxAmplitude) maxAmplitude = vReal[i];
    }

    // Vẽ từng cột
    for (int i = 0; i < numBars; i++) {
        int sampleIndex = i * barStep;
        if (sampleIndex >= SAMPLES / 2) break;

        // Chuẩn hóa biên độ
        int barHeight = map(vReal[sampleIndex], 0, maxAmplitude, 0, SCREEN_HEIGHT - 1);

        // Vẽ cột
        display.drawLine(i, SCREEN_HEIGHT - 1, i, SCREEN_HEIGHT - 1 - barHeight, SSD1306_WHITE);
    }

    // Hiển thị nhãn trục
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("0 Hz"); // Tần số bắt đầu
    display.setCursor(SCREEN_WIDTH - 30, 0);
    display.print(SAMPLING_FREQUENCY / 2); // Tần số Nyquist (giới hạn trên)

    display.display();  // Cập nhật màn hình
}



void loop() {

  DisplayFullFrequencySpectrum();
  //Max_Frequency();
}