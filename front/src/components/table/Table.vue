<template>
  <div>
    <v-row
      align="center"
      justify="center">
      <v-col md="3">
        <v-switch
          class="mx-2"
          dark
          v-model="onLive"
          color="red darken-3"
          label="On live">
        </v-switch>
      </v-col>
      <v-col>
        <template v-if="onEdit">
          <v-btn
            class="mx-2"
            fab
            dark
            color="pink"
            @click="saveEdit">
            <v-icon dark>
              mdi-save-alt
            </v-icon>
          </v-btn>
          <v-btn
            class="mx-2"
            fab
            dark
            color="teal"
            @click="cancelEdit">
            <v-icon dark>
              mdi-cancel
            </v-icon>
          </v-btn>
        </template>
        <template v-else>
            <v-btn
              class="mx-2"
              fab
              dark
              color="primary"
              @click="sendMqtt">
              <v-icon dark>
                mdi-cloud-upload
              </v-icon>
            </v-btn>
            <v-btn
              class="mx-2"
              fab
              dark
              color="pink"
              @click="addRecord">
              <v-icon dark>
                mdi-plus
              </v-icon>
            </v-btn>
            <v-btn
              class="mx-2"
              fab
              dark
              color="teal"
              :disabled="!isOneSelected"
              @click="editItem">
              <v-icon dark>
                mdi-pencil
              </v-icon>
            </v-btn>
            <v-btn
              class="mx-2"
              fab
              dark
              color="purple"
              @click="removeSelection"
              :disabled="!isSelected">
              <v-icon dark>
                mdi-minus
              </v-icon>
            </v-btn>
            <v-btn
              class="mx-2"
              fab
              dark
              color="indigo"
              @click="playTable"
              :disabled="isEmpty">
              <v-icon dark>
                mdi-play-circle-outline
              </v-icon>
            </v-btn>

            <v-btn
              class="mx-2"
              fab
              dark
              color="cyan"
              @click="exportJson">
              <v-icon dark>
                mdi-share
              </v-icon>
            </v-btn>


        </template>
      </v-col>
    </v-row>
    <v-row
      align="center"
      justify="center">
      <v-col>
        <v-data-table
          v-model="selected"
          :headers="headerList"
          :items="tableData"
          :single-select="singleSelect"
          item-key="id"
          show-select
          class="elevation-1">

          <template v-slot:item.actions="{ item }">
            <v-icon
              small
              class="mr-2">
              mdi-pencil
            </v-icon>
            <v-icon
              small
              @click="deleteItem(item)">
              mdi-delete
            </v-icon>
          </template>
        </v-data-table>
      </v-col>
    </v-row>
  </div>
</template>

<script>
export default {
  name: "Table",
  props: {
    record: {
      type: Object,
      require: true
    },
    headerList: {
      type: Array,
      require: true
    }
  },
  data() {
    return {
      headers: this.headerList,
      tableData: [],
      singleSelect: false,
      selected: [],
      mtopic: "/dofIn",
      live: true,
      stepper: true,
      onEdit: false,
      onLive: false,
    }
  },
  watch: {
    tableData(newValue) {
      this.$log.debug('tableData newValue', newValue)
      this.$emit('input', newValue)
    },
    record(newValue) {
      this.$log.debug('record newValue', this.record, newValue)
      if (this.onLive) {
        this.$mqtt.publish(this.mtopic, this.record)
      }
     }
  },
  computed: {
    model: {
      get() {
        this.$log.debug('model get', this.tableData)
        return this.tableData
      },
      set(value) {
        this.$log.debug('model set', value)
        this.$emit('input', value)
      }
    },
    isOneSelected() {
      return this.selected.length === 1
    },
    isSelected() {
      return this.selected.length > 0
    },
    isEmpty() {
      return this.tableData.length === 0
    }
  },
  methods: {
    onEnable() {
      if (this.onEdit) {
        return false
      }
      return true
    },
    saveEdit() {
      this.$log.debug('saveEdit', this.record, this.editedItem)
      const id = this.editedItem.id
      this.editedItem = this.record
      this.editedItem.id = id

      this.tableData = this.tableData.map(servo => {
        if (servo.id === id) {
          servo = this.editedItem
        }
        return servo
      })
      this.editedItem = null
      this.selected = []
      this.onEdit = false
      this.$emit('on-edit-saved')
    },
    cancelEdit() {
      this.editedItem = null
      this.selected = []
      this.onEdit = false
      this.$emit('on-edit-cancel')
    },
    editItem() {
      this.onEdit = true
      this.editedItem = Object.assign({}, this.selected[0])
      this.$emit('on-edit-item', this.editedItem)
    },
    deleteItem(item) {
      this.editedIndex = this.tableData.indexOf(item)
      this.editedItem = Object.assign({}, item)
      this.dialogDelete = true
    },

    addRecord() {
      this.$log.debug('addRecord', this.record)

      const lastItem = this.tableData[this.tableData.length - 1]
      let id = lastItem && lastItem.hasOwnProperty('id') ? lastItem.id : 1

      let row = Object.assign({}, this.record)
      row['id'] = id + 1
      this.$log.debug(row)
      this.tableData.push(row)
    },
    removeSelection() {
      this.selected.forEach((row) => {
        this.tableData.forEach((r) => {
          if (r.id === row.id) {
            this.$log.debug(r, row)
            this.tableData.splice(this.tableData.indexOf(row), 1);
          }
        });
      })
      this.selected = []
    },
    sendMqtt() {
      this.$mqtt.publish(this.mtopic, this.record)
    },
    exportJson() {
      const json = JSON.stringify(this.tableData)
      const blob = new Blob([json], {
        type: `application/json`
      });
      const link = document.createElement("a");
      link.href = window.URL.createObjectURL(blob);
      link.download = `robotdata.json`;
      link.click();
    },
    playTable() {
      this.tableData.forEach((r) => {
        this.$mqtt.publish(this.mtopic, r)
      })
    },
  },
  created() {
    this.$log.debug('created')
    this.$mqtt.startMqtt().then(res => {
      if (res) {
        this.$mqtt.subscribe(this.mtopic)
        this.$mqtt.mqttMessage((topic, message) => {
          this.$log.debug("topic ", topic)
          this.$log.debug("message ", JSON.stringify(message))
        })
        //this.$mqtt.publish("dofIn", this.record)
      }
    })
  },
  destroyed() {
    this.$mqtt.endMqtt()
  },
}
</script>

<style scoped>

</style>
