
var _ = require('lodash');
var HID = require('node-hid');

// ontrack device ids:
var ontrackVendorId = 0x0a07;
var ontrackProductId = 0x00d0;

function findDevice(vendorId, productId){

	console.log("Looking for device: vendor = " + vendorId + ", product = " + productId);

	var devices = HID.devices();
	var device = _.first(_.filter(devices, function(device){
		return (device.vendorId == vendorId) && (device.productId == productId);
	}));
	console.log("Found path: " + device.path);
	return new HID.HID(device.path);
}

function readPort(){
	device.write([0x00, 0x01, 0x01, 0x05, 0xff, 0xff]);
}

var device = findDevice(ontrackVendorId, ontrackProductId);
if(!device){
	throw new Error("Could not find ontrack device in HID devices list");
}
console.log("Found device: " + JSON.stringify(device));

device.on('data', function(data){
	console.log("RECEIVED DATA: " + JSON.stringify(data));
});

device.on('error', function(err){
	console.log("DEVICE ERROR: " + err);
});

setTimeout(function(){
	console.log("Sending data to device...");
	device.write(['P', 'I', 0x00, 0x00, 0x00, 0x00, 0x00]);
}, 500);