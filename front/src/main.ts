import Vue from 'vue'
import App from './App.vue'
import router from './router'
import theme from '@/theme'
import mMQTT from './mqtt-vue';
import vuetify from './plugins/vuetify';

Vue.prototype.$mqtt = mMQTT;

Vue.config.productionTip = false

Vue.use(theme)

new Vue({
  router,
  vuetify,
  render: h => h(App)
}).$mount('#app')
