
# Install Hellboy on Kali
![](https://github.com/user-attachments/assets/9ae054ce-c8fc-4b6f-94a7-f1562d27eef2)
![](https://github.com/user-attachments/assets/5e4b35f0-9f69-4d47-9a77-40288dd748b7)



## 1. Install the dependencies for LARB, DWM, and lolcat for the `.zshrc`
> [!Note]
> If you get errors while installing, try using `kali-tweaks` to change to `Network Repositories` > `Mirrors: Cloudflare`.

```
sudo apt-get update && sudo apt-get install -y lolcat libxft-dev libharfbuzz-dev libxinerama-dev libx11-xcb-dev libxcb-res0-dev whiptail curl wget sudo zsh git build-essential feh alacritty xorg xserver-xorg x11-utils xinit x11-xserver-utils fonts-league-mono  fonts-font-awesome fonts-dejavu  bc xcompmgr x11-utils arandr dosfstools libnotify-bin dunst calcurse exfatprogs nsxiv xwallpaper ffmpeg ffmpegthumbnailer gnome-keyring neovim mpd mpc mpv man-db ncmpcpp newsboat fonts-noto fonts-noto-color-emoji ntfs-3g wireplumber pipewire-pulse pulsemixer sc-im maim abook unclutter unzip lynx xcape xclip xdotool yt-dlp zathura poppler-utils mediainfo atool fzf task-spooler socat moreutils tesseract-ocr-eng tesseract-ocr tesseract-ocr-eng suckless-tools dwm chromium fastfetch
```

## 2. Get and run the script
> [!Note]
> This setup uses the Alacritty terminal. You can customize it by editing `~/.config/alacritty/alacritty.toml`.

```
wget https://raw.githubusercontent.com/blue-pho3nix/dwm-love/refs/heads/main/hellboy/hellboy-alacritty-terminal.sh && sudo bash hellboy-alacritty-terminal.sh
```

## 3. Log out and login using `DWM`

![image](https://github.com/user-attachments/assets/962e46d6-903b-499b-a6b9-9ae2094cf3a4)

--- 

## Find out info on your new DWM setup click on the `?` in the statusbar

![image](https://github.com/user-attachments/assets/35a1a856-4789-4bf9-8c2c-8700093652b9)

## If you just want the dotfiles, you can get em here:

- [dotfiles](https://github.com/blue-pho3nix/dwm-love/tree/hellboy-alacritty-dotfiles)

```
git clone -b hellboy-alacritty-dotfiles https://github.com/blue-pho3nix/dwm-love.git
```
