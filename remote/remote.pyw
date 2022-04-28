from pynput import keyboard
import requests
add="http://192.168.4.1/drive?"
speed=300
def on_press(key):
    global speed
    if key==keyboard.Key.up:
        requests.get(add+"direction=forward&speed="+str(speed))
    elif key==keyboard.Key.down:
        requests.get(add+"direction=backward&speed="+str(speed))
    elif key==keyboard.Key.left:
        requests.get(add+"direction=left&speed="+str(speed))
    elif key==keyboard.Key.right:
        requests.get(add+"direction=right&speed="+str(speed))
    elif key==keyboard.Key.space:
        requests.get(add+"direction=forward&speed=0")
    elif key==keyboard.Key.ctrl:
        requests.get(add+"direction=ccw&speed="+str(200))
    elif key==keyboard.Key.alt:
        requests.get(add+"direction=cw&speed="+str(200))       
def on_release(key):
    global speed
    if key==keyboard.Key.up:
        requests.get(add+"direction=forward&speed="+"0")
    elif key==keyboard.Key.down:
        requests.get(add+"direction=backward&speed="+"0")
    elif key==keyboard.Key.left:
        requests.get(add+"direction=left&speed="+"0")
    elif key==keyboard.Key.right:
        requests.get(add+"direction=right&speed="+"0")
    elif key==keyboard.Key.space:
        requests.get(add+"direction=forward&speed=0")
    elif key==keyboard.Key.ctrl:
        requests.get(add+"direction=ccw&speed="+"0")
    elif key==keyboard.Key.alt:
        requests.get(add+"direction=cw&speed="+"0")  
listener = keyboard.Listener(on_press=on_press,on_release=on_release)
listener.start()
listener.join() 