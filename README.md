# Tap-reader

For reading and parsing tap device ethernet frame data, this codes block also implement go packet interface reader.

# Run

1. **TAP Device Reader Program**

Clone the repo and make sure that you have c compiler installed

`gcc main.c -o tap_reader`

```
sudo ./tap_reader <tap-device-name>
```

2. **Network Interface Reader Program.**
   The interface logger is golang based application make sure that you have [go](https://go.dev/doc/install) installed and [libpcap](https://www.cyberithub.com/how-to-install-libpcap-dev-package-on-ubuntu-20-04-lts-focal/) that help to capture the packet in any linux desto
   `go run cmd/main.go`
