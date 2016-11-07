from pico2d import *


class SoundManager:
    def __init__(self):
        self.BGM_Play = load_music('Resource\Sound\BGM\BGM_Play.ogg')
        self.SE_Punch = load_music('Resource\Sound\Effect\Punch.ogg')
        self.SE_Kick = load_music('Resource\Sound\Effect\Kick.mp3')
        self.SE_Kamehameha = load_music('Resource\Sound\Effect\Kamehameha.mp3')
        self.SE_PowerUp_Sound = load_music('Resource\Sound\Effect\PowerUp_Sound.mp3')
        self.SE_PowerUp = load_music('Resource\Sound\Effect\PowerUp.mp3')
        self.SE_PowerUp2 = load_music('Resource\Sound\Effect\PowerUp2.mp3')
        self.SE_Move = load_music('Resource\Sound\Effect\Move.mp3')
        self.SE_Boss_Crashed = load_music('Resource\Sound\Effect\Boss_Crashed.ogg')
        self.SE_Crash_Impact = load_music('Resource\Sound\Effect\Crash_Impact.ogg')
        self.SE_Meteor_Crashed = load_music('Resource\Sound\Effect\Meteor_Crashed.ogg')


