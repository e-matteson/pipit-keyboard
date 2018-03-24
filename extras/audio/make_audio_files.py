#!/bin/python2


from __future__ import division

import subprocess
from time import sleep
import os

# for generating sound files
import numpy as np
import matplotlib.pyplot as plt
import scipy.io.wavfile
import scipy.signal as sig
import scipy.stats as stats

master_volume = 1
sounds = {
    'A':{'filename':'tick1.wav',
         'volume': .9,
         'freq': 10,
         'length': .01,
         'quality': 1,
         'tone':'sawtooth',
         'a': 2,
         'b': 10,},
    'W':{'filename':'tick2.wav',
         'volume': .8,
         'freq': 5,
         'length': .01,
         'quality': .8,
         'tone':'sawtooth',
         'a': 2,
         'b': 5,},
    'M':{'filename':'tick3.wav',
         'volume': .8,
         'freq': 10,
         'length': .05,
         'quality': .95,
         'tone':'sawtooth',
         'a': 2,
         'b': 5,},
    'S':{'filename':'tick4.wav',
         'volume': .4,
         'freq': 50,
         'length': .04,
         'quality': .6,
         'tone':'sawtooth',
         'a': 2,
         'b': 5,},
    'U':{'filename':'tick5.wav',
         'volume': .5,
         'freq': 40,
         'length': .02,
         'quality': .9,
         'tone':'sawtooth',
         'a': 2,
         'b': 5,},
}

def construct_sound(params, plot_sound=False):
    print "constructing sound: %s" % params['filename']
    rate = 44100
    N = int(rate*params['length'])
    time = range(N)

    if params['tone'] == 'sawtooth':
        raw = sig.sawtooth(np.linspace(0,params['freq'],N))
    elif params['tone'] == 'sine':
        # not succesfully tested, try plotting
        raw = np.sin(np.linspace(0,params['freq'],N))
    else:
        raise RuntimeError('unknown tone type')

    noise = np.random.uniform(-1, 1, N) # 44100 random samples between -1 and 1
    envelope = stats.beta(params['a'],params['b']).pdf([n/N for n in time])

    data = raw*params['quality'] + noise*(1-params['quality'])
    data *= envelope
    save_wav(data, params['filename'], params['volume'])
    if plot_sound:
        figure()
        plt.plot(time, raw)
        plt.plot(time, envelope)
        plt.plot(time, data)
        plt.show()


def save_wav(data, filename, volume=1):
    total_volume = volume * master_volume
    if total_volume > 1 or total_volume < 0:
        raise RuntimeError('volume out of range')
    scaled_data = np.int16(data/np.max(np.abs(data)) * total_volume * 32767)
    scipy.io.wavfile.write(filename, 44100, scaled_data)


def main():
    data = [0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8] * 10000
    save_wav(data, "test.wav")
    # for code in sounds.keys():
    #     construct_sound(sounds[code])

main()
