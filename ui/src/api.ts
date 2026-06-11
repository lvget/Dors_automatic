import { AppState } from './stor'
import { toast } from 'vue-sonner'

function getJson(url: string, params?: unknown) {
  //const queryString = new URLSearchParams(params).toString()`${baseUrl}?${queryString}`

  return new Promise((resolve) => {
    fetch(AppState.baseUrl + url, {
      method: 'GET',
      cache: 'no-store',
    })
      .then((resp) => resp.json().then(resolve))
      .catch((err) => {
        showError(err.message)
        resolve(null)
      })
  })
}

function post(url: string, params?: unknown) {
  return new Promise<string>((resolve) => {
    fetch(AppState.baseUrl + url, {
      method: 'POST',
      body: params ? JSON.stringify(params) : null,
    })
      .then((resp) => {
        resp.text().then(resolve)
      })
      .catch((err) => {
        showError(err.message)
        //resolve('Error')
      })
  })
}

function showError(err: string) {
  console.error(err)
  toast.error(err)
}

const api = {
  getSettings() {
    return getJson('/settings')
  },
  saveSettings(data: unknown) {
    return post('/settings', data)
  },
  getFiles() {
    return getJson('/files')
  },
  ioCommand(id: string, value: any) {
    return post(`/io?id=${id}&value=${value}`)
  },
  ioValues() {
    return getJson('/io')
  },
}

export default api
