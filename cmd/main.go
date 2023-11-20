package main

import (
	"fmt"
	"log"
	"os"
	"os/signal"

	"github.com/google/gopacket"
	"github.com/google/gopacket/layers"
	"github.com/google/gopacket/pcap"
)

var ethName = "eth0"

func main() {

	handle, err := pcap.OpenLive(ethName, 1600, true, pcap.BlockForever)
	if err != nil {
		log.Fatal(err)
	}
	defer handle.Close()

	packetSource := gopacket.NewPacketSource(handle, handle.LinkType())

	// Handle interrupt signal for graceful termination
	interrupt := make(chan os.Signal, 1)
	signal.Notify(interrupt, os.Interrupt)

	for {
		select {
		case packet := <-packetSource.Packets():

			if tcpLayer := packet.Layer(layers.LayerTypeTCP); tcpLayer != nil {
				tcp, _ := tcpLayer.(*layers.TCP)

				srcIP := packet.NetworkLayer().NetworkFlow().Src().String()
				dstIP := packet.NetworkLayer().NetworkFlow().Dst().String()

				srcPort := tcp.SrcPort.String()
				dstPort := tcp.DstPort.String()

				fmt.Printf("Source: %s:%s -> Destination: %s:%s\n", srcIP, srcPort, dstIP, dstPort)

				payload := tcp.Payload
				fmt.Printf("Payload: %x\n", payload)
			}
		case <-interrupt:
			fmt.Println("Interrupt signal received. Exiting...")
			return
		}
	}
}
