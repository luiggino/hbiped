import VueLogger from 'vuejs-logger'
const isProduction = process.env.NODE_ENV === 'production'

const options = {
  isEnabled: true,
  logLevel: isProduction ? 'error' : 'debug',
  stringifyArguments: false,
  showLogLevel: true,
  showMethodName: true,
  separator: '|',
  showConsoleColors: true
}

const Logger = {
  install(Vue: any) {
    Vue.use(VueLogger, options)
  }
}

export default Logger
