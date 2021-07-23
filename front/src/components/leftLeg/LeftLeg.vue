<template>
  <div>
    <v-row v-for="servo in servos" :key="servo.name"
           align="center"
           justify="center">
      <v-col cols="2">
        <Servo :name="servo.l.name" v-model="servo.l.value" v-if="positionBeside(servo)"></Servo>
      </v-col>
      <v-col cols="2">
        <Servo :name="servo.l.name" v-model="servo.l.value" v-if="positionCenter(servo)"></Servo>
      </v-col>
      <v-col cols="2">
        <Servo :name="servo.r.name" v-model="servo.r.value" v-if="positionCenter(servo)"></Servo>
      </v-col>
      <v-col cols="2">
        <Servo :name="servo.r.name" v-model="servo.r.value" v-if="positionBeside(servo)"></Servo>
      </v-col>
    </v-row>
  </div>
</template>

<script lang="ts">
import {Component, Prop, Vue} from "vue-property-decorator";
import Servo from "@/components/servo/Servo.vue";
import {PositionEnum} from "@/model/PositionEnum";
import {IServo} from "@/model/IServo";

@Component({
  components: {
    Servo,
  },
})
export default class LeftLeg extends Vue {
  @Prop({
    required: true,
    type: Array as () => Array<IServo>,
    default: () => {
      return []
    }
  }) servos!: Array<IServo>


  public positionBeside(item: IServo): boolean {
    return item.position === PositionEnum.Beside
  }

  public positionCenter(item: IServo): boolean {
    return item.position === PositionEnum.Center
  }
}
</script>

<style scoped>

</style>
