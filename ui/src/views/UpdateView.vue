<template>
  <div>
    <div class="text-3xl">Обновление прошивки</div>
    <iframe :src="AppState.baseUrl + '/update'" style="border: none; width: 100%; height: 400px;"></iframe>
  </div>
</template>

<script lang="ts" setup>
import { AppState } from '@/stor'
</script>
