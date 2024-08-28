# Light 🔆
Lightweight unix console app for brightness control.

## Examples
Get
```
$ light
> 128/255 (50%)
```
Set
```
$ light 100
> 100/255 (39%)

$ light 70%
> 179/255 (70%)
```
Increment
```
$ light -29
> 150/255 (58%)

$ light +5%
> 161/255 (61%)
```

## Install
1. Clone the repository
   ```sh
   git clone https://github.com/dekabu/light
   cd light
   ```
2. Determine where the `brightness` and `max_brightness` files are located on your system
   (*/sys/class/backlight/amdgpu_bl0/\** by default)
> [!WARNING]
> Make sure your user has write access to the `brightness` file.

3. Correct define in `light.c`
   ```c
   6. #define PREFIX <put your prefix>
   ```

4. Build
   ```
   make
   ```

5. Install
   ```
   make install
   ```
