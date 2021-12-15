# saga-pixelflut

This is a [pixelflut](https://github.com/defnull/pixelflut) implementation for [SAGA-GIS](http://www.saga-gis.org/en/index.html). 

## Pixelflut

[Pixelflut](https://github.com/defnull/pixelflut) is a multiplayer network canvas with a intentional inefficient network protocol.
The Server are often beefy-machines with high bandwidth on large hacker-events. 
The goal for all player is to implement the inefficient protocol as efficient as they can, to be on the foreground. 
  
This Repository provides a SAGA-Tool to play Pixelflut from my favourite GIS-Application. My first Milestone is a simple running client to optimize it on upcoming events.

## Usage
### Dependencies 
- `SAGA-GIS`
- [SAGA-GIS Dependencies](https://sourceforge.net/p/saga-gis/wiki/Compiling%20SAGA%20on%20Linux/ )
- `boost` I use Boost because i expect the `asio` part to be largely adopt by `std`
  
### Build
Clone the Repository:
```
git clone https://github.com/sptzmllr/saga-pixelflut
cd saga-pixelflut
```
Build in Debug-Mode
```
DEBUG=1 make
```
For Debugging use `GDB`.
  
Build in Release-Mode
```
make
```
Load the Tool-Library in SAGA: *Geoprocessing > Load Tool Library*. Select the `saga_pixelflut.so` in the Repository in the File-Dialog.

## Todo

- [ ] Bring it to work, lol.
- [ ] Migrate to CMake
- [ ] Use wxNetwork and boost and make it a build option
- [ ] Windows Support
- [ ] Make it fast
