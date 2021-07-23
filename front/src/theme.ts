//import GlobalComponents from '@/ElementUiComponents'
import Logger from '@/logger'
//import { BootstrapVue, IconsPlugin } from 'bootstrap-vue'

//import 'bootstrap/dist/css/bootstrap.min.css'
//import 'bootstrap-vue/dist/bootstrap-vue.css'

export default {
  async install (Vue: any) {
  //  Vue.use(GlobalComponents)
    Vue.use(Logger)
   // Vue.use(BootstrapVue)
  }
}
