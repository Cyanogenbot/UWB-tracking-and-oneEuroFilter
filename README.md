# UWB-tracking-and-oneEuroFilter

Simple script for reading UWB tags, filtering, and uploding to oocsi (homeassistant included).
Written for a Arduino nano connect 2040

## OneEuroFilter
oneEuroFilter library made to be as simple as possible.

### Initialisation
```oneEuroFilter euro = oneEuroFilter(0,0.0,1.0,0.0,1.0);```
### Using the filter
```int x = euro.filter(time, x);```
