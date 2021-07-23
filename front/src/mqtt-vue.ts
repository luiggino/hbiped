import mqtt from "mqtt";
let client: any = {};
export default {
  startMqtt() {
    return new Promise((resove, reject) => {
      console.log('conecting....')
      /*const url = "wss://localhost:8883"
      const username = 'username';
      const password = 'password';*/
      const options = {
        clientId: 'web-client',
        connectTimeout: 5000,
        hostname: '127.0.0.1',
        port: 1883,
        //path: '/mqtt'
      };

      //client = mqtt.connect(options);
      client = mqtt.connect('mqtt://localhost:8883')
      //client = mqtt.connect('mqtt://172.16.0.100:9001')
      client.on("connect", (e: any) => {
        console.log("mqtt!", e);
        resove(true);
      });
      client.on("error", (e: any) => {
        console.log("mqtt!", e);
        reject('mqtt');
      });
    });
  },
  endMqtt() {
    console.log("mqtt!");
    client.end();
  },
  mqttMessage(callback: any) {
    client.on("message", (topic: any, message: any) => {
      callback(topic, message);
    });
  },
  subscribe(topic: any) {
    console.log("mqtt(" + topic + ")");
    client.subscribe(topic);
  },
  publish(topic: any, message: any) {
    console.log(
      "mqtt (" + topic + ") " + JSON.stringify(message)
    );
    client.publish(topic, JSON.stringify(message));
  }
};
