
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

device.resume();

// if(device._paused){
// 	console.log("Device is paused...resuming");
// 	device.resume();
// 	console.log("Now device: " + JSON.stringify(device));
// }

function sendToDevice(){
	console.log("Sending data to device...");
	// device.write(['P', 'I', 0x00, 0x00, 0x00, 0x00, 0x00]);
	// device.write(['P', 'B']);
	device.write([1, 'P', 'B', 0, 0, 0, 0, 0]);
	setTimeout(sendToDevice, 500);
}
// console.log("Sending data to device...");
// device.write([1, 'P', 'B', 0, 0, 0, 0, 0]);

// setTimeout(function(){ console.log("zzzz");}, 5000);

device.write([1, 'P', 'B', 0, 0, 0, 0, 0]);

var timer = setTimeout(sendToDevice, 500);
// timer = setTimeout(sendToDevice, 500);
// sendToDevice();
// device.read(function(err, data){
// 	console.log("READ ERR: " + err);
// 	console.log("READ: " + data);
// });