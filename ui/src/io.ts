export enum PIN_MODE {
  ON = 0,
  OFF,
  AUTO,
}

export const PIN_MODE_TEXT = ['ВКЛ', 'ВЫКЛ', 'АВТО']

export type IoPin = {
  name: string
  id: string
  type: IoType
}

export enum IoType {
  OUTPUT = 0,
  INPUT = 1,
}

export const io: IoPin[] = [
  {
    name: 'Лампа левая',
    id: 'LampL',
    type: IoType.OUTPUT,
  },
  {
    name: 'Лампа правая',
    id: 'LampR',
    type: IoType.OUTPUT,
  },
  {
    name: 'Гардероб',
    id: 'LampIn',
    type: IoType.OUTPUT,
  },
  {
    name: 'Дверь левая',
    id: 'SwL',
    type: IoType.INPUT,
  },
  {
    name: 'Дверь правая',
    id: 'SwR',
    type: IoType.INPUT,
  },
  {
    name: 'Дверь входная',
    id: 'SwDor',
    type: IoType.INPUT,
  },
]
