##**Rapport d'avancement du projet - Toutes les tâches demandées ont été mises en place :**

## **Côté serveur :**

 - Fenêtre d'application affichant une image SVG dont le nom est passé en argument ✓
 - Image SVG rendue dynamiquement à l'écran et modifiée en mémoire instantanément à chaque message client reçu ✓
 - Serveur UDP ✓
 - Utilisation de la RFC CBOR pour l'envoie et la réception des messages ✓
 - Système de typage pour les attributs respectant la grammaire de type des attributs SVG ✓
 - Attribut style pilotable (seulement avec le client console) ✓
 - Système d'interpolation de valeur entre l'ancienne et la nouvelle valeur en fonction d'un delay précisé en attribut, **oui, même pour les couleurs** ✓
 - Parsing d'expression (valeur calculées) lors de la réception d'un message (prise en compte d'un grand nombre de fonction logique et mathématique grâce à la libraire Exprtk) ✓

## **Côté client :**

 - Client console intelligent ✓
 - Client graphique épuré ✓
 - Communication avec le serveur sous forme de datagramme UDP ✓
 - Architecture MV (Modèle - Vue) pour une intégration plus simple de plusieurs type de client (console, graphique, ...) ✓

