import { reactive } from 'vue'
import api from './api'

const AppState = reactive({
  baseUrl: '',

  save() {
    localStorage.setItem('baseUrl', this.baseUrl)
  },
  load() {
    this.baseUrl = localStorage.getItem('baseUrl') || ''
  },
})

const ServerState = reactive({
  settings: {} as Record<string, any>,
  ioValues: {} as Record<string, any>,
  save() {
    api.saveSettings(this.settings)
  },

  load() {
    api.getSettings().then((data) => {
      if (data) {
        ServerState.settings = data
        //toast('Settings loaded')
      }
    })
  },
  getValues() {
    api.ioValues().then((data) => {
      if (data) {
        ServerState.ioValues = data
      }
    })
  },
})

AppState.load()
ServerState.load()

export { AppState, ServerState }
