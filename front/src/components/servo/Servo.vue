<template>
  <v-card flat>
    <v-card-title>{{ name }}</v-card-title>
    <v-card-text>
      <v-row>
        <v-col class="pr-4">
          <v-slider
            v-model="model"
            class="align-center"
            :max="max"
            :min="min"
            thumb-label="always">
          </v-slider>
        </v-col>
      </v-row>
    </v-card-text>
  </v-card>
</template>

<script>
export default {
  components: {},
  props: {
    name: {
      type: String,
    },
    value: {
      type: [Number, Array],
      default: 90
    },
    vertical: {
      type: Boolean,
      default: false
    },
    min: {
      type: Number,
      default: 0,
    },
    max: {
      type: Number,
      default: 180,
    }
  },
  computed: {
    model: {
      get() {
        return this.value
      },
      set(value) {
        console.log('servo ', value)
        this.$emit('input', value)
      }
    }
  },
}
</script>

<style>
</style>
