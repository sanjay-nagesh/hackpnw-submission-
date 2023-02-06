# light turn on when person will walk in and turn off when LAST person walks out
# there will also be a 2 light sensors on each side of door
#    in order to track whether people ar leaving or entering
# there also is a light switch that will overrule the light sensor  if the person wishes to turn the light off while in the room

# if switch 1 is tripped && there is no one in room, turn on light

# if switch 2 is tripped && there is 1 person in the room, turn off light

# if switch 1 is tripped && some one is in tne toom, do nothing

# if switch 2 is tripped && some one is in the room, do nothing

# import keyboard

# x = natural light = 0
# CODE:
people = 0
# switch 1 is just outside of room
switchOut = False
# switch 2 is just inside the room
switchIn = False


light = False

cont = True


def updateLight(state):
    # if state == "out" then switchOut = true
    global switchOut
    global switchIn
    global light
    if state == "out":
        switchOut = True
    # if state == "in" then switchIn = true
    if state == "in":
        switchIn = True

    # if outside switch is tripped && there is no one in room, turn on light
    if switchOut and people == 0:
        light = True
    # if inside switch is tripped && there is 1 person in room, turn off light
    elif switchIn and people == 1:
        light = False
    # if outside switch is tripped && some one is in the toom, do nothing
    # elif switchOut and people != 0:
    # if inside switch is tripped && some one is in the room, do nothing

    switchOut = False
    switchIn = False

    # elif switchIn and people != 1:


# If keyboard key a pressed then set switch out = TRUE and call update light
# people = 0
def switch():
    global light
    light = not light


# keyboard.add_hotkey('l',switch)
##keyboard.add_hotkey(')

while True:
    # keyboard.on_press_key("l", lambda: setattr(light, not light))
    if input("Switch: ") == "l":
        switch()

    if not ((people == 0 and light) or (people != 0 and not light)):
        input = input("Enter: ")
        input2 = input("Enter 2: ")
        if input == "a" and input2 == "d":
            updateLight("out")
            people += 1
        elif input == "d" and input2 == "a":
            updateLight("in")
            people -= 1

    if light:
        print("Light on")
    else:
        print("Light off")
    print("people")
