import pygame
import serial
import time


# Stelt Serial Communicatie op met Arduino, COM is de poort op je laptop waar de kabel zit, kan verschillen met apparaat
# we proberen verschillende COM poorten tot een werkende gevonden wordt
arduino = None
comlijst = ['COM1', 'COM2', 'COM3', 'COM4', 'COM5']

for comport in comlijst:
    try:
        arduino = serial.Serial(comport, 9600, timeout=1)
        print(f"Verbonden met Arduino op {comport}")
        time.sleep(2)
        break
    except:
        print(f"Kon {comport} niet openen.")

if arduino is None:
    print("Geen Arduino gevonden.")
    verbonden = 0
else:
    verbonden = 1

# Deze code stuurt de commando door en stuurt een update bericht in de Shell
def sendCommand(command):
    if verbonden == 1:
        arduino.write(command.encode())
    print(f"Sent command: {command}")

# Initialiseert Pygame
pygame.init()
screen = pygame.display.set_mode((640, 480))
pygame.display.set_caption("The field")

running = True
lastCommand = None  

# Een While loop wat kijkt welke toetsen er op de gebruiker's computer wordt ingedrukt, en dat opzet in commands van 1 tot 8, die de 8 bewegingsstaten Representeren.
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    keys = pygame.key.get_pressed()

    if keys[pygame.K_w] and keys[pygame.K_d]:
        command = '1'
# Command 1 is motor vooruit en stuur naar rechts
       
    elif keys[pygame.K_w] and keys[pygame.K_a]:
        command = '2'
# Command 2 is motor vooruit en stuur naar links
       
    elif keys[pygame.K_w]:
        command = '3'
# Command 3 is motor vooruit

    elif keys[pygame.K_s] and keys[pygame.K_d]:
        command = '4'
# Command 4 is motor achteruit en stuur naar rechts

    elif keys[pygame.K_s] and keys[pygame.K_a]:
        command = '5'
# Command 5 is motor achteruit en stuur naar links

    elif keys[pygame.K_s]:
        command = '6'
# Command 6 is motor achteruit

    elif keys[pygame.K_d]:
        command = '7'
# Command 7 is stuur naar rechts
       
    elif keys[pygame.K_a]:
        command = '8'
# Command 8 is stuur naar links

    else:
        command = '0'
# Command 0 betekent GEEN motor aandrijving

# Deze stuk code zorgt dat de signaal om de motoren te stoppen door blijft sturen in het geval dat het niet opgevangen wordt de eerste keer.
    if command == '0':
        sendCommand('0')
        time.sleep(0.20)

# Deze stuk code zorgt dat codes niet overbodig gestuurt worden, omdat er anders te veel commandos gestuurt kunnen worden, wat de auto kan overbelasten
    if command != lastCommand:
        sendCommand(command)
        lastCommand = command

    pygame.display.flip()
    pygame.time.delay(100)

pygame.quit()
if verbonden == 1:
    arduino.close()