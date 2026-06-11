<template>
  <div>
    {{ data }}
  </div>
</template>

<script setup lang="ts">
const props = defineProps<{ data: unknown }>()
</script>

<style scoped></style>
