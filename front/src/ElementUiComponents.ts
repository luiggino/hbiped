import ElementUI from 'element-ui'
import 'element-ui/lib/theme-chalk/index.css'

const GlobalComponents = {
  install(Vue: any) {
    Vue.use(ElementUI)
  }
}

export default GlobalComponents
