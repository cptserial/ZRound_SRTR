<div align="center">

# ZRound SRTR
  
![Build with PlatformIO](https://img.shields.io/badge/build%20with-PlatformIO-orange?logo=data%3Aimage%2Fsvg%2Bxml%3Bbase64%2CPHN2ZyB3aWR0aD0iMjUwMCIgaGVpZ2h0PSIyNTAwIiB2aWV3Qm94PSIwIDAgMjU2IDI1NiIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiBwcmVzZXJ2ZUFzcGVjdFJhdGlvPSJ4TWlkWU1pZCI+PHBhdGggZD0iTTEyOCAwQzkzLjgxIDAgNjEuNjY2IDEzLjMxNCAzNy40OSAzNy40OSAxMy4zMTQgNjEuNjY2IDAgOTMuODEgMCAxMjhjMCAzNC4xOSAxMy4zMTQgNjYuMzM0IDM3LjQ5IDkwLjUxQzYxLjY2NiAyNDIuNjg2IDkzLjgxIDI1NiAxMjggMjU2YzM0LjE5IDAgNjYuMzM0LTEzLjMxNCA5MC41MS0zNy40OUMyNDIuNjg2IDE5NC4zMzQgMjU2IDE2Mi4xOSAyNTYgMTI4YzAtMzQuMTktMTMuMzE0LTY2LjMzNC0zNy40OS05MC41MUMxOTQuMzM0IDEzLjMxNCAxNjIuMTkgMCAxMjggMCIgZmlsbD0iI0ZGN0YwMCIvPjxwYXRoIGQ9Ik0yNDkuMzg2IDEyOGMwIDY3LjA0LTU0LjM0NyAxMjEuMzg2LTEyMS4zODYgMTIxLjM4NkM2MC45NiAyNDkuMzg2IDYuNjEzIDE5NS4wNCA2LjYxMyAxMjggNi42MTMgNjAuOTYgNjAuOTYgNi42MTQgMTI4IDYuNjE0YzY3LjA0IDAgMTIxLjM4NiA1NC4zNDYgMTIxLjM4NiAxMjEuMzg2IiBmaWxsPSIjRkZGIi8+PHBhdGggZD0iTTE2MC44NjkgNzQuMDYybDUuMTQ1LTE4LjUzN2M1LjI2NC0uNDcgOS4zOTItNC44ODYgOS4zOTItMTAuMjczIDAtNS43LTQuNjItMTAuMzItMTAuMzItMTAuMzJzLTEwLjMyIDQuNjItMTAuMzIgMTAuMzJjMCAzLjc1NSAyLjAxMyA3LjAzIDUuMDEgOC44MzdsLTUuMDUgMTguMTk1Yy0xNC40MzctMy42Ny0yNi42MjUtMy4zOS0yNi42MjUtMy4zOWwtMi4yNTggMS4wMXYxNDAuODcybDIuMjU4Ljc1M2MxMy42MTQgMCA3My4xNzctNDEuMTMzIDczLjMyMy04NS4yNyAwLTMxLjYyNC0yMS4wMjMtNDUuODI1LTQwLjU1NS01Mi4xOTd6TTE0Ni41MyAxNjQuOGMtMTEuNjE3LTE4LjU1Ny02LjcwNi02MS43NTEgMjMuNjQzLTY3LjkyNSA4LjMyLTEuMzMzIDE4LjUwOSA0LjEzNCAyMS41MSAxNi4yNzkgNy41ODIgMjUuNzY2LTM3LjAxNSA2MS44NDUtNDUuMTUzIDUxLjY0NnptMTguMjE2LTM5Ljc1MmE5LjM5OSA5LjM5OSAwIDAgMC05LjM5OSA5LjM5OSA5LjM5OSA5LjM5OSAwIDAgMCA5LjQgOS4zOTkgOS4zOTkgOS4zOTkgMCAwIDAgOS4zOTgtOS40IDkuMzk5IDkuMzk5IDAgMCAwLTkuMzk5LTkuMzk4em0yLjgxIDguNjcyYTIuMzc0IDIuMzc0IDAgMSAxIDAtNC43NDkgMi4zNzQgMi4zNzQgMCAwIDEgMCA0Ljc0OXoiIGZpbGw9IiNFNTcyMDAiLz48cGF0aCBkPSJNMTAxLjM3MSA3Mi43MDlsLTUuMDIzLTE4LjkwMWMyLjg3NC0xLjgzMiA0Ljc4Ni01LjA0IDQuNzg2LTguNzAxIDAtNS43LTQuNjItMTAuMzItMTAuMzItMTAuMzItNS42OTkgMC0xMC4zMTkgNC42Mi0xMC4zMTkgMTAuMzIgMCA1LjY4MiA0LjU5MiAxMC4yODkgMTAuMjY3IDEwLjMxN0w5NS44IDc0LjM3OGMtMTkuNjA5IDYuNTEtNDAuODg1IDIwLjc0Mi00MC44ODUgNTEuODguNDM2IDQ1LjAxIDU5LjU3MiA4NS4yNjcgNzMuMTg2IDg1LjI2N1Y2OC44OTJzLTEyLjI1Mi0uMDYyLTI2LjcyOSAzLjgxN3ptMTAuMzk1IDkyLjA5Yy04LjEzOCAxMC4yLTUyLjczNS0yNS44OC00NS4xNTQtNTEuNjQ1IDMuMDAyLTEyLjE0NSAxMy4xOS0xNy42MTIgMjEuNTExLTE2LjI4IDMwLjM1IDYuMTc1IDM1LjI2IDQ5LjM2OSAyMy42NDMgNjcuOTI2em0tMTguODItMzkuNDZhOS4zOTkgOS4zOTkgMCAwIDAtOS4zOTkgOS4zOTggOS4zOTkgOS4zOTkgMCAwIDAgOS40IDkuNCA5LjM5OSA5LjM5OSAwIDAgMCA5LjM5OC05LjQgOS4zOTkgOS4zOTkgMCAwIDAtOS4zOTktOS4zOTl6bS0yLjgxIDguNjcxYTIuMzc0IDIuMzc0IDAgMSAxIDAtNC43NDggMi4zNzQgMi4zNzQgMCAwIDEgMCA0Ljc0OHoiIGZpbGw9IiNGRjdGMDAiLz48L3N2Zz4=) ![Arduino](https://img.shields.io/badge/Arduino-Uno_R4_Minima-Green?logo=arduino) ![C++](https://img.shields.io/badge/C++-00599C?logo=C%2B%2B) ![SparkFun](https://img.shields.io/badge/Spark-Fun-crimson?logo=sparkfun)</div>

An Arduino sketch that turns a SparkFun Simultaneous RFID Tag Reader (SRTR) into an RC car lap timing device. Designed primarily for Kyosho "Mini-Z" RC cars and similar, but could probably be used with larger cars with the right antenna and tags.

## Table of Contents
- [Idea](#idea)
- [Parts Needed](#parts-needed)
- [Antenna Selection](#antenna-selection)
- [Tag Selection](#tag-selection)

# Idea
ZRound is an open protocol for RC car lap timing devices. Most of these devices are based on infrared transponders that have to be powered from the car's battery and visible through a window. A few are based on RFID technology, but they either use the older 13.5Mhz tags, or they use powered RFID transponders. Both have significant drawbacks.

I have a small RCP track for my Mini-Z cars in my garage. I wanted a system that was based on RFID, but used inexpensive and readily available UHF tags. 

The SparkFun Simultaneous RFID Tag Reader (SRTR) is an Arduino HAT designed to lower the bar to tinkering with UHF RFID technology. I though it would be the perfect vehicle to develop such a timing device.

# Parts Needed
To build a ZRound SRTR, you need:
- [Arduino Uno R4 Minima](https://store.arduino.cc/pages/uno-r4)

  <img alt="The Arduino R4 Minima" src="https://github.com/cptserial/ZRound_SRTR/assets/5551724/fba5b56f-4696-40d2-8bac-2b6e41ce4964" width="445px" />
  
- [SparkFun Simultaneous RFID Tag Reader](https://www.sparkfun.com/products/14066)
  
  <img src="https://github.com/cptserial/ZRound_SRTR/assets/5551724/634655da-342a-4c9b-b9de-6a6c947be718" width="445px" />

- [Appropriate antenna](#antenna-selection)
- UFL to (antenna connector on your antenna) adapter

  <img src="https://github.com/cptserial/ZRound_SRTR/assets/5551724/ab9a17df-d180-4a0f-9f72-7fec2ecd26c4" width="445px" />

- 3D printed enclosure
- 5V 2A power adapter

# Antenna Selection
Selecting the right antenna is critical to getting good reads of the tags as they pass.
* [FEIG ID ANT.U LOCFIELD® Antenna](https://www.feig-electronics.com/en/products/identification/product/id-antu-locfieldr/) - above the track
  Also known as the Harting Locfield Ha-Vis Travelling Wave Antenna. Works great but it doesn't like to touch the ground during operation, so it needs to be suspended from a bridge.
  Use the 1.5m version for 3-tile wide 30CM RCP track or 2-tile 50CM RCP track. Use the 2.5m version for 3-tile 50CM RCP track.
  
  <img src="https://github.com/cptserial/ZRound_SRTR/assets/5551724/d33821bc-21fb-4989-bf5f-4f131f8dd170" width="445px">

* [FlexiRay SF2 Ultra Slim RFID Antenna](https://www.flexiray.com/products/sf2/) - Above or below the track
  (Still testing) Super thin, so you can pass it under the track. May require milling of the track underside.
  Use the SF-2421 (with pigtail) or SF-2401 (flush connector) for 3-tile wide 30CM RCP track or 2-tile 50CM RCP track.

  <img src="https://github.com/cptserial/ZRound_SRTR/assets/5551724/1c104a4c-40b1-4580-9611-6ce1bda479d0" width="445px">

# Tag Selection
  
