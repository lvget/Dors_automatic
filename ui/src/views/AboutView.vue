<template>
  <div class="about">
    <h1 class="text-3xl">ESP2866</h1>
    <h3>files:</h3>

    <Table>
      <TableHeader>
        <TableRow>
          <TableHead>
            File
          </TableHead>
          <TableHead>Size</TableHead>

        </TableRow>
      </TableHeader>
      <TableBody>
        <TableRow v-for="(f, i) in files" :key="i">
          <TableCell class="font-medium">{{ f.name }}</TableCell>
          <TableCell>{{ f.size / 1000 }} kB</TableCell>
        </TableRow>
      </TableBody>
    </Table>
  </div>
</template>

<script lang="ts" setup>
import { ref } from 'vue'
import api from '../api'
import {
  Table,
  TableBody,
  TableCaption,
  TableCell,
  TableFooter,
  TableHead,
  TableHeader,
  TableRow,
} from '@/components/ui/table'

const files = ref<any[]>([]);

files.value = []
api.getFiles().then((data: any) => files.value = data.sort((a: any, b: any) => b.name > a.name ? 1 : -1));

</script>
