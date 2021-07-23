import {IServoObject} from "@/model/IServoObject";
import {PositionEnum} from "@/model/PositionEnum";

export type IServo = {
  l: IServoObject,
  r: IServoObject,
  position: PositionEnum,
}
