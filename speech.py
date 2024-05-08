import speech_recognition as sr
import serial
import time

DIRECTIONS = ['left', 'right', 'forward', 'backward', 'forwards', 'backwards', 'front', 'back']


def detect_english_speech():
    recognizer = sr.Recognizer()

    with sr.Microphone() as source:
        try:
            print("Recording your audio.............")
            audio_data = recognizer.record(source, duration=5)
            print("Recognizing your text.............")
            text = recognizer.recognize_google(audio_data)
            print(text)
            return text
        except sr.UnknownValueError:
            print("Sorry, I couldn't understand what you said.")
            return None
        except sr.RequestError as e:
            print("Could not request results from Google Speech Recognition service; {0}".format(e))
            return None


def write_read(x, arduino):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline().decode()
    return data


def main():
    arduino = serial.Serial(port='COM8', baudrate=9600, timeout=.1)
    time.sleep(3)

    while True:
        word = detect_english_speech()
        if word:
            word = word.lower().strip().rstrip()
            print(f"Detected word:{word}")

            if  word in DIRECTIONS:
                value = write_read(word[0], arduino)
                print(f'Received from Arduino: {value}')

main()