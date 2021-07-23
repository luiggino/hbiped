<template>
  <grid-layout :layout.sync="model"
               :col-num="12"
               :row-height="50"
               :is-draggable="draggable"
               :is-resizable="resizable"
               :vertical-compact="true"
               :use-css-transforms="true"
               :margin="[10, 10]">
    <grid-item v-for="item in model"
               :key="item.code"
               :static="item.static"
               :x="item.x"
               :y="item.y"
               :w="item.w"
               :h="item.h"
               :i="item.i">
      <v-tooltip top v-if="item.servo">
        <template v-slot:activator="{ on, attrs }">
        <Servo :name="item.code"
               v-model="item.value"
               v-bind="attrs"
               :min="itemMin(item)"
               :max="itemMax(item)"
               v-on="on"></Servo>
        </template>
        <span>{{item.code}} shit</span>
      </v-tooltip>
      <span class="text" v-else> </span>

    </grid-item>
  </grid-layout>
</template>

<script>
import {GridItem, GridLayout} from "vue-grid-layout"
import Servo from "@/components/servo/Servo.vue";

export default {
  name: "GridDraggable",
  components: {
    GridLayout,
    GridItem,
    Servo
  },
  data() {
    return {
      //draggable: true,
      resizable: false,
      index: 0
    }
  },
  props: {
    value: {
      type: [Number, Array],
      default: 90
    },
    draggable: {
      type: Boolean,
      default: false
    }
  },
  computed: {
    model: {
      get: function () {
        return this.value
      },
      set: function(value) {
        console.log(value)
        this.$emit('input', value)
      }
    }
  },
  methods: {
    itemTitle(item) {
      let result = item.i;
      if (item.static) {
        result += " - Static";
      }
      return result;
    },
    itemMin(item) {
      if (item.hasOwnProperty('min')) {
        return item.min
      }
      return 0
    },
    itemMax(item) {
      if (item.hasOwnProperty('max')) {
        return item.max
      }
      return 180
    }
  },
  watch: {
    'model': {
      handler(newValue, oldValue) {
        //console.log('model ', newValue)
        if (newValue.length > 0) {
          this.$emit('input', this.model)
        }
      },
      deep: true
    }
  }
}
</script>

<style scoped>
.vue-grid-layout {
  background: #eee;
}

.vue-grid-item:not(.vue-grid-placeholder) {
  background: #ccc;
  border: 1px solid black;
}

.vue-grid-item .resizing {
  opacity: 0.9;
}

.vue-grid-item .static {
  background: #cce;
}

.vue-grid-item .text {
  font-size: 24px;
  text-align: center;
  position: absolute;
  top: 0;
  bottom: 0;
  left: 0;
  right: 0;
  margin: auto;
  height: 100%;
  width: 100%;
}

.vue-grid-item .no-drag {
  height: 100%;
  width: 100%;
}

.vue-grid-item .minMax {
  font-size: 12px;
}

.vue-grid-item .add {
  cursor: pointer;
}

.vue-draggable-handle {
  position: absolute;
  width: 20px;
  height: 20px;
  top: 0;
  left: 0;
  background: url("data:image/svg+xml;utf8,<svg xmlns='http://www.w3.org/2000/svg' width='10' height='10'><circle cx='5' cy='5' r='5' fill='#999999'/></svg>") no-repeat;
  background-position: bottom right;
  padding: 0 8px 8px 0;
  background-repeat: no-repeat;
  background-origin: content-box;
  box-sizing: border-box;
  cursor: pointer;
}

</style>
