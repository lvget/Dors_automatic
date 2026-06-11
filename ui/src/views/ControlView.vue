<template>
  <div>

    <h1 class="text-3xl">Управление</h1>
    <table class="table-auto border-collapse border border-gray-300 border-spacing-2">
      <tbody>
        <tr v-for="pin in io" :key="pin.id">
          <td class="border border-gray-300 p-1">{{ pin.name }}</td>
          <td class="border border-gray-300 p-1" border-gray-300>{{ pinMode(pin.id) }}</td>
          <td class="border border-gray-300 p-1" border-gray-300>
            <Button class="m-1" @click="setSettingValue(pin.id, PIN_MODE.ON)">On</Button>
            <Button class="m-1" @click="setSettingValue(pin.id, PIN_MODE.OFF)">Off</Button>
            <Button class="m-1" @click="setSettingValue(pin.id, PIN_MODE.AUTO)">Auto</Button>
          </td>
        </tr>
      </tbody>
    </table>
    <Button class="m-2" @click="ServerState.load()">Обновить</Button>
    <!-- <Button @click="ServerState.save()">Save</Button> -->
    <div>{{ ServerState.settings }}</div>

  </div>
</template>

<script setup lang="ts">
import { Button } from '@/components/ui/button'
import { ServerState } from '@/stor'
import { io, PIN_MODE, PIN_MODE_TEXT } from '@/io'


function setSettingValue(id: string, v: any) {
  ServerState.settings[id] = v
  ServerState.save()
}

function pinMode(id: string) {
  return PIN_MODE_TEXT[ServerState.settings[id]] || '?'
}
</script>

<style scoped></style>
