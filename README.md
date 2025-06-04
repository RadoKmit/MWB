# Minecraft World Backup (MWB)

MWB is a simple C++ tool to backup Minecraft worlds by copying the world folders and storing them with date-stamped names.

## Features

- Copies Minecraft world folders recursively
- Automatically names backups with current date
- Configurable source and destination paths via JSON config file

## Getting Started

### Build

Requires C++17 and CMake.

```bash
git clone https://github.com/RadoKmit/MWB.git
cd MWB
mkdir build && cd build
cmake ..
make
```
### Usage
Run the executable:
./MWB /(path to config file)

Config file example (config.json)
```
{
  "path": {
    "source": "/home/user/.minecraft/saves",
    "destination": "/home/user/minecraft_backups"
  },
  "worlds": {
    "world": "world",
    "nether": "world_nether",
    "the_end": "world_the_end"
  },
  "backupsbackupsToKeep": 10
}
```

#### License

This project is licensed under the MIT License.

Feel free to open issues or submit pull requests!
