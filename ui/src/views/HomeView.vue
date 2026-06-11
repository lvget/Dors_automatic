<template>
  <div>

    <h1 class="text-3xl">Управление</h1>
    <table class="table-auto border-collapse border border-gray-300 border-spacing-2">
      <tbody>
        <tr v-for="pin in io" :key="pin.id">
          <td class="border border-gray-300 p-1">{{ pin.name }}</td>
          <td class="border border-gray-300 p-1" border-gray-300>{{ getValue(pin.id) }}</td>
          <td class="border border-gray-300 p-1" border-gray-300>
            <div v-if="pin.type == IoType.OUTPUT">
              <Button class="m-1" @click="api.ioCommand(pin.id, PIN_MODE.ON)">On</Button>
              <Button class="m-1" @click="api.ioCommand(pin.id, PIN_MODE.OFF)">Off</Button>
            </div>
          </td>
        </tr>
      </tbody>
    </table>
    <Button class="m-2" @click="loadIOValue()">Обновить</Button>
    <!-- <Button @click="ServerState.save()">Save</Button> -->
    <div>{{ ioValues }}</div>

  </div>
</template>

<script setup lang="ts">
import { reactive, onUnmounted } from 'vue'
import { Button } from '@/components/ui/button'
import { ServerState } from '@/stor'
import { io, IoType, PIN_MODE, PIN_MODE_TEXT } from '@/io'
import api from '@/api'

const ioValues = reactive<Record<string, number>>({});

//const timer = setInterval(() => loadIOValue(), 5000)

onUnmounted(() => {
  //clearInterval(timer)
})

function loadIOValue() {
  api.ioValues().then((data) => {
    if (data) {
      Object.assign(ioValues, data)
    }
  })
}

function getValue(id: string) {
  return PIN_MODE_TEXT[ioValues[id]!] || '!'
}

function pinMode(id: string) {
  return PIN_MODE_TEXT[ServerState.settings[id]] || '?'
}
</script>

<style scoped></style>
