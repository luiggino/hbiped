<template>
  <v-container
    class="fill-height"
    fluid>
    <v-row>
      <v-col cols="6">
        <GridDraggable v-model="layout"
                       :draggable="false"></GridDraggable>
      </v-col>
      <v-col cols="6">
        <Table :headerList="headerList"
               :record="record"
               @on-edit-item="editItem"
               @on-edit-cancel="editCancel"
               @on-edit-saved="editSaved"></Table>
      </v-col>

    </v-row>
  </v-container>
</template>

<script>
import Servo from "@/components/servo/Servo.vue";
import Table from "@/components/table/Table.vue";
import LeftLeg from "@/components/leftLeg/LeftLeg.vue";
import GridDraggable from "@/components/GridDraggable/GridDraggable.vue";

export default {
  name: "Home",
  components: {
    GridDraggable,
    LeftLeg,
    Servo,
    Table
  },
  data() {
    return {
      layout: [
        {"x": 0, "y": 0, "w": 2, "h": 3, "i": "0"},
        {"x": 2, "y": 0, "w": 2, "h": 3, "i": "1"},
        {"x": 4, "y": 0, "w": 2, "h": 3, "i": "2", servo: true, name: 'head', code: 'S6', pos: 6, value: 90},
        {"x": 6, "y": 0, "w": 2, "h": 3, "i": "3"},
        {"x": 8, "y": 0, "w": 2, "h": 3, "i": "4"},

        {"x": 1, "y": 5, "w": 2, "h": 3, "i": "5", servo: true, name: 'arm left 1', code: 'S7', pos: 7, value: 90},
        {"x": 3, "y": 5, "w": 2, "h": 3, "i": "6", servo: true, name: 'shoulder left', code: 'S6', pos: 6, value: 90},
        {
          "x": 5,
          "y": 5,
          "w": 2,
          "h": 3,
          "i": "7",
          servo: true,
          name: 'shoulder right',
          code: 'S14',
          pos: 14,
          value: 90
        },
        {"x": 7, "y": 5, "w": 2, "h": 3, "i": "8", servo: true, name: 'arm right 1', code: 'S15', pos: 15, value: 90},

        {"x": 0, "y": 10, "w": 2, "h": 3, "i": "9", servo: true, name: 'elbow left 1', code: 'S5', pos: 5, value: 90},
        {"x": 3, "y": 10, "w": 2, "h": 3, "i": "10", servo: true, name: 'hip left', code: 'S4', pos: 4, value: 90},
        {"x": 5, "y": 10, "w": 2, "h": 3, "i": "11", servo: true, name: 'hip right', code: 'S12', pos: 12, value: 90},
        {
          "x": 8,
          "y": 10,
          "w": 2,
          "h": 3,
          "i": "12",
          servo: true,
          name: 'elbow right 1',
          code: 'S13',
          pos: 13,
          value: 90
        },

        {"x": 3, "y": 15, "w": 2, "h": 3, "i": "10", servo: true, name: 'thigh left', code: 'S3', pos: 3, value: 90},
        {"x": 5, "y": 15, "w": 2, "h": 3, "i": "11", servo: true, name: 'thigh right', code: 'S11', pos: 11, value: 90},

        {"x": 3, "y": 20, "w": 2, "h": 3, "i": "10", servo: true, name: 'knee left', code: 'S2', pos: 2, value: 90},
        {"x": 5, "y": 20, "w": 2, "h": 3, "i": "11", servo: true, name: 'knee right', code: 'S10', pos: 10, value: 90},

        {"x": 3, "y": 25, "w": 2, "h": 3, "i": "10", servo: true, name: 'foot left', code: 'S1', pos: 1, value: 90, min: 56, max: 171},
        {"x": 5, "y": 25, "w": 2, "h": 3, "i": "11", servo: true, name: 'foot right', code: 'S9', pos: 9, value: 90}]

    }
  },
  computed: {
    record: {
      get() {
        console.log('record get')

        const list = this.layout
          .filter(servoObj => servoObj.hasOwnProperty('code'))
          .sort((a, b) => a.pos - b.pos)
          .map((servoObj) => ({[servoObj.code]: servoObj.value}))

        const newObj = Object.assign({}, ...list)
        console.log("record", newObj)

        return newObj
      },
      set(value) {
        console.log("record set")
      }
    },
    headerList() {
      const list = this.layout
        .filter(servoObj => servoObj.hasOwnProperty('code'))
        .sort((a, b) => a.pos - b.pos)
        .flatMap(servoObj => [{text: servoObj.code, value: servoObj.code}])

      console.log("header ", list)
      this.$log.debug('headerList', list)
      return list
    },
  },
  methods: {
    editItem(item) {
      this.layout = this.layout.map(servo => {
        if (!servo.hasOwnProperty('code')) {
          return servo
        }
        this.$log.debug(item.hasOwnProperty(servo.code), servo.code, servo.value, item['S13'])
        if (item.hasOwnProperty(servo.code)) {
          servo.value = item[servo.code]
        }
        this.$log.debug(servo.value)
        return servo
      })
      this.$log.debug(item, this.layout)
    },
    editCancel() {
      this.layout = this.layout.map(servo => {
        if (!servo.hasOwnProperty('code')) {
          return servo
        }
        servo.value = 90
        return servo
      })
    },
    editSaved() {
      this.layout = this.layout.map(servo => {
        if (!servo.hasOwnProperty('code')) {
          return servo
        }
        servo.value = 90
        return servo
      })
    }
  }

}
</script>
