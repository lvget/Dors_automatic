<template>
  <div>
    <h1 class="text-3xl">Настройки</h1>


    <div class="m-4">
      <div class="text-2xl">Подключение</div>
      <table>
        <tr>
          <td>Адрес</td>
          <td>
            <ButtonGroup class="">
              <Input placeholder="device url" v-model="AppState.baseUrl" />
              <Button variant="outline" @click="test()">Test </Button>
              <Button variant="outline" @click="AppState.save(); load();"> OK </Button>
            </ButtonGroup>
          </td>
        </tr>
      </table>
    </div>

    <div v-for="setting in SettingsOptions" class="m-4">
      <div class="text-2xl">{{ setting.title }}</div>
      <table>
        <tr v-for="(v, k) in setting.items" :key="v.id">
          <td>{{ v.name }}</td>
          <td>
            <Input v-model="settings[v.id]" :type="v.type" />
          </td>
        </tr>
      </table>
    </div>


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

const SettingsOptions = [{
  title: 'Настройки',
  items: [
    {
      id: 'intervalLED',
      name: 'Интервал LED',
      type: 'number',
    },
    {
      id: 'nightBegin',
      name: 'Ночь начинается, час',
      type: 'number',
    },
    {
      id: 'nightEnd',
      name: 'Ночь заканчивается, час',
      type: 'number',
    },
    {
      id: 'autoOffMinute',
      name: 'Авто выключение, минут',
      type: 'number',
    },
    {
      id: 'mp3FileNumber',
      name: 'Файл для звонка',
      type: 'number',
    },
    {
      id: 'vkAccessToken',
      name: 'vkAccessToken',
      type: 'string',
    },
    {
      id: 'vkUserId',
      name: 'vkUserId',
      type: 'string',
    },
  ]
},
{
  title: 'Режимы IO',
  items: [
    {
      id: 'LampL',
      name: 'Лампа левая',
      type: 'number',
    },
    {
      id: 'LampR',
      name: 'Лампа правая',
      type: 'number',
    },
    {
      id: 'LampIn',
      name: 'Лампа в гардеробе',
      type: 'number',
    },
    {
      id: 'SwR',
      name: 'Выключатель правый',
      type: 'number',
    },
    {
      id: 'SwL',
      name: 'Выключатель левый',
      type: 'number',
    },
    {
      id: 'SwDor',
      name: 'Входная дверь',
      type: 'number',
    },
    {
      id: 'Doorbell',
      name: 'Кнопка звонка',
      type: 'number',
    },
  ]
}
];

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
