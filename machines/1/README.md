# Machines 1 : Moon LoopStation

![mon image](docs/img/front.jpg)



> La documentation en français est placée en bas de page.



# Tutorial video

Here is the link of the youtube video

# SD Card Image
download [here](http://assoundessens.fr/bigfiles/lucibox/moonloopstation.gz)

## Features

Moon LoopStation is a 4 channels looper, able to save and open session, and load .wav files, with a low latency sound card.

- 4 sync and independant channels
- save and open session over 12 memory
- add reverb and delay to you sound
- stop all / play all button
- wifi connection to open .wav files
- 3 leds per channel , avoid confusion
- compact and made with footswith



# What do you need ?



## Components



| Amount | Name                           | Ebay link                                                    |
| ------ | ------------------------------ | ------------------------------------------------------------ |
| 9      | Footswitch                     | [link](https://www.ebay.com/sch/i.html?_from=R40&_nkw=momentary+foot+switch+guitar) |
| 1      | standard switch                | [link](https://www.ebay.com/sch/i.html?_from=R40&_nkw=push+button+switch) |
| 3      | potentiometer                  | [link](https://www.ebay.com/sch/i.html?_from=R40&_nkw=potentiometer) |
| 13     | JR cable                       | [link](https://www.ebay.com/sch/i.html?_from=R40&_nkw=jr+cable) |
| 1      | sensor shield                  | [link](https://www.ebay.com/sch/i.html?_from=R40&_nkw=sensor+shield) |
| 12     | led addressable . 60 led / m . | [link](https://www.ebay.com/sch/i.html?_from=R40&_trksid=m570.l1313&_nkw=WS2812+60leds%2Fm) Probably can't buy under 1m |

## Boards



| Name      | type        | price ( + or -) | link                                                         |
| --------- | ----------- | --------------- | ------------------------------------------------------------ |
| Arduino   | arduino uno | 7 euros         | [link1](http://arduino.cc) [link2](https://www.ebay.com/sch/i.html?_from=R40&_trksid=m570.l1313&_nkw=uno+arduino+board+-ch340) |
| Raspberry | model 3     | 35 euros        | [link](https://www.kubii.fr/les-cartes-raspberry-pi/1628-raspberry-pi-3-modele-b-1-gb-kubii-640522710850.html) |
| PiSound   | -           | 99 euros        | [link](http://blockas.io)                                    |



## Raspberry Pi extras

| Name             | spec                                          | price ( + or -) |
| ---------------- | --------------------------------------------- | --------------- |
| RPI power supply | 5v, micro usb, 2A min., ( official is better) | 10 euros        |
| micro sd card    | 8 gb , class 10                               | 10 euros        |



# Materials

- Aluminium composite panel ( Dibond ) plate ( 400 mm * 460 mm minimum)
- Wood ( 40mm thickness min)  300mm X 10 mm
- wood screw



# Tools

- Drill ( with metal drill )
- Wood saw
- Electronic soldering iron
- Cutter ( big and fat)
- Big and fat rule
- Probably clamp and other extra stuff



# Layout

![mon image](docs/img/complete.png)



# How does it work?



## Volumes, level

Input volumes and output are set from the PiSound card, and its potentiometer.

## channels

There is 4 channels. Each channel has

- 1 footswitch record ( one press start recording, one press ends recording)
- 1 footswitch play ( **short press**) or delete (**long press**)
- 1 led red : recording
- 1 led white : a loop is recorded, exist
- 1 led green : a loop is playing



## stop all / play all  / delete all button

**short press** 

This button stop all channel actually playing, and play all the channels stopped

**long press = RESET**

This action delete all the loops, and is equivalent to a <u>reset</u> of the pedal.



## Syncro of recording

### Case 1 : Nothing is playing

If there is no loop playing, then the loopstation is stopped.

Press the record button one time to start recording, then press again to stop recording.

 At the point, the recording of a new loop is going to set a new tempo to the loopstation

### Case 2 : One or more loop are playing

If there is already loops playing, then the tempo is already set. Once you press the record button, the looper is waiting for the new  cycle before recording. At this point,  the red led of recording is blinking.

Once the cycle start, the led is red and not blinking anymore, and the looper is recording. Your recording can be longer than the previous one ! When you finish, one press of the rec button begin the stop precedure: the red led is blinking unitl the next cycle.

At least, channels can be set of different size, but are always multiple one from each other.



## Syncro of playing







