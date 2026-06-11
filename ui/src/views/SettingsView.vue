<template>
  <div>
    <h1 class="text-3xl">Настройки</h1>

    <ButtonGroup class="m-4">
      <Input placeholder="device url" v-model="AppState.baseUrl" />
      <Button variant="outline" @click="test()">Test </Button>
      <Button variant="outline" @click="AppState.save(); load();"> OK </Button>
    </ButtonGroup>

    <table>
      <tr v-for="(v, k) in settings" :key="k">
        <td>{{ k }}</td>
        <td>
          <Input v-model="settings[k]" type="number" />
          <!-- <input :value="v" @input="settings[k] = parseFloat($event.target?.value) || 0" type="number" /> -->
        </td>
      </tr>
    </table>

    <div class="flex flex-wrap items-center gap-2 md:flex-row m-4">
      <Button @click="save()">
        <SaveIcon />
        Сохранить
        <!-- <Spinner class="animate-spin" /> -->
      </Button>
    </div>
    {{ settings }}
  </div>
</template>
<script lang="ts" setup>
import { ref } from 'vue'
import api from '../api'
import { ArrowUpIcon, GitBranchIcon, SaveIcon } from '@lucide/vue'
import { Button } from '@/components/ui/button'
import { Input } from '@/components/ui/input'
import { Spinner } from '@/components/ui/spinner'
import { ButtonGroup } from '@/components/ui/button-group'
import { toast } from 'vue-sonner'
import { AppState } from '@/stor'

const settings = ref<any>({})

settings.value = {
  intervalLED: 1000,
}

function test() {
  toast('Event has been created')

  // api.saveSettings(settings.value)
}
function save() {
  api.saveSettings(settings.value)
}

function load() {
  api.getSettings().then((data) => {
    if (data) {
      settings.value = data
      toast('Settings loaded')
    }

  })
}

load()
</script>
